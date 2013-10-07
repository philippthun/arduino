#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "Credentials.h"

/********************************************************************************/

// Interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBEN  5
#define ADAFRUIT_CC3000_CS    10

// SPI pins
// MOSI <-> 11
// MISO <-> 12
// CLK  <-> 13

// Power pins
// VIN  <-> 5V
// GND  <-> GND

/********************************************************************************/

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBEN, SPI_CLOCK_DIV2);

char buffer[64];
int length;

char commandAction;

/********************************************************************************/

void setup(void) {
  Serial.begin(115200);

  resetCommand();

  printUsage();
}

/********************************************************************************/

void loop(void) {
  if (Serial.available() > 0) {
    receiveCommand();
  }

  if (commandAction == 'a') {
    Serial.println(F("\n=== Initialising Wifi module..."));
    initWifiModule();
    resetCommand();
  }
  else if (commandAction == 'b') {
    Serial.println(F("\n=== Checking firmware version..."));
    checkFirmwareVersion();
    resetCommand();
  }
  else if (commandAction == 'c') {
    Serial.println(F("\n=== Displaying MAC address..."));
    displayMACAddress();
    resetCommand();
  }
  else if (commandAction == 'd') {
    Serial.println(F("\n=== Listing networks..."));
    listNetworks();
    resetCommand();
  }
  else if (commandAction == 'e') {
    Serial.println(F("\n=== Connecting to AP..."));
    connectToAP();
    resetCommand();
  }
  else if (commandAction == 'f') {
    Serial.println(F("\n=== Displaying connection details..."));
    displayConnectionDetails();
    resetCommand();
  }
  else if (commandAction == 'g') {
    Serial.println(F("\n=== Pinging Google..."));
    pingGoogle();
    resetCommand();
  }
  else if (commandAction == 'h') {
    Serial.println(F("\n=== Disconnect..."));
    disconnect();
    resetCommand();
  }
  else if (commandAction == 'i') {
    Serial.println(F("\n=== Displaying status..."));
    displayStatus();
    resetCommand();
  }

  delay(50);
}

/********************************************************************************/

void resetCommand() {
  commandAction = ' ';
}

void printUsage() {
  Serial.println(F("\n=== Usage ==="));
  Serial.println(F("a - Initialise Wifi module"));
  Serial.println(F(" b - Check firmware version"));
  Serial.println(F(" c - Display MAC address"));
  Serial.println(F(" d - List networks"));
  Serial.println(F(" e - Connect to AP"));
  Serial.println(F("  f - Display connection details"));
  Serial.println(F("  g - Ping Google"));
  Serial.println(F("  h - Disconnect"));
  Serial.println(F("i - Display status"));
}

void receiveCommand() {
  length = Serial.readBytesUntil('.', buffer, 64);

  commandAction = buffer[0];
  if (commandAction < 'a' || commandAction > 'i') {
    Serial.println(F("\n=== Illegal action"));
    resetCommand();
  }
}

/********************************************************************************/

void initWifiModule(void) {
  if (!cc3000.begin()) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.println(F("=== Ok"));
  }
}

void checkFirmwareVersion(void) {
  uint8_t major, minor;

  if(!cc3000.getFirmwareVersion(&major, &minor)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.print(F("=== Firmware version: "));
    Serial.print(major);
    Serial.print(F("."));
    Serial.println(minor);
    uint16_t version = major;
    version <<= 8;
    version |= minor;

    if ((version != 0x113) && (version != 0x118)) {
      Serial.println(F("=== Wrong!"));
    }
    else {
      Serial.println(F("=== Ok"));
    }
  }
}

void displayMACAddress(void) {
  uint8_t macAddress[6];

  if(!cc3000.getMacAddress(macAddress)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.print(F("=== MAC address: "));
    cc3000.printHex((byte*)&macAddress, 6);
  }
}

void listNetworks(void) {
  uint32_t index;
  uint8_t valid, rssi, sec;
  char ssidname[33];

  if (!cc3000.startSSIDscan(&index)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.print(F("=== Networks found: "));
    Serial.println(index);

    while (index) {
      index--;

      valid = cc3000.getNextSSID(&rssi, &sec, ssidname);

      Serial.print(F("\n=== SSID name    : "));
      Serial.println(ssidname);
      Serial.print(F("=== RSSI         : "));
      Serial.println(rssi);
      Serial.print(F("=== Security mode: "));
      Serial.println(sec);
    }
  }

  cc3000.stopSSIDscan();
}

void connectToAP(void) {
  char *ssid = WLAN_SSID;
  Serial.print(F("=== Attempting to connect to "));
  Serial.print(ssid);
  Serial.println("...");
  if(!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.println(F("=== Ok"));
    Serial.println(F("\n=== Waiting for DHCP to complete..."));
    int timer = 10000;
    while ((timer > 0) && !cc3000.checkDHCP()) {
      delay(10);
      timer -= 10;
    }
    if (timer <= 0) {
      Serial.println(F("=== Timed out!"));
    }
    else {
      Serial.println(F("=== Ok"));
    }
  }
}

void displayConnectionDetails(void) {
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.print(F("=== IP Addr: "));
    cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\n=== Netmask: "));
    cc3000.printIPdotsRev(netmask);
    Serial.print(F("\n=== Gateway: "));
    cc3000.printIPdotsRev(gateway);
    Serial.print(F("\n=== DHCPsrv: "));
    cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\n=== DNSserv: "));
    cc3000.printIPdotsRev(dnsserv);
    Serial.println();
  }
}

void pingGoogle(void) {
  uint32_t ip;
  Serial.println(F("=== Resolving host name..."));
  if (!cc3000.getHostByName("www.google.com", &ip)) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.println(F("=== Ok"));
    Serial.print(F("\n=== Pinging "));
    cc3000.printIPdotsRev(ip);
    Serial.println(F("..."));
    uint8_t replies = cc3000.ping(ip, 5, 1000);
    Serial.print(F("=== "));
    Serial.print(replies);
    Serial.println(F(" successful replies"));
  }
}

void disconnect(void) {
  if (!cc3000.disconnect()) {
    Serial.println(F("=== Failed!"));
  }
  else {
    Serial.println(F("=== Ok"));
  }
}

void displayStatus(void) {
  Serial.print(F("=== Status: "));
  Serial.println(cc3000.getStatus());
  Serial.print(F("=== Connected: "));
  Serial.println(cc3000.checkConnected());
  Serial.print(F("=== DHCP: "));
  Serial.println(cc3000.checkDHCP());
}

