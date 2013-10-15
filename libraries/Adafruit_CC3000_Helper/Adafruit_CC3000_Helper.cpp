/*
  Adafruit CC3000 Helper

  Reusable helper functions for the Adafruit CC3000 library
  (https://github.com/adafruit/Adafruit_CC3000_Library). Most functions have been taken from or are
  inspired by the library's examples.
*/

#include "Adafruit_CC3000.h"
#include "Adafruit_CC3000_Helper.h"

bool initWifiModule(Adafruit_CC3000 &cc3000) {
  if (!cc3000.begin()) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.println(F("=== Ok"));
    return true;
  }
}

bool checkFirmwareVersion(Adafruit_CC3000 &cc3000) {
  uint8_t major, minor;

  if(!cc3000.getFirmwareVersion(&major, &minor)) {
    Serial.println(F("=== Failed!"));
    return false;
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
      return false;
    }
    else {
      Serial.println(F("=== Ok"));
      return true;
    }
  }
}

bool displayMacAddress(Adafruit_CC3000 &cc3000) {
  uint8_t macAddress[6];

  if(!cc3000.getMacAddress(macAddress)) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.print(F("=== MAC address: "));
    cc3000.printHex((byte*) &macAddress, 6);
    return true;
  }
}

bool listNetworks(Adafruit_CC3000 &cc3000) {
  uint32_t index;
  uint8_t rssi, securityMode;
  char ssid[33];

  if (!cc3000.startSSIDscan(&index)) {
    Serial.println(F("=== Failed!"));
    cc3000.stopSSIDscan();
    return false;
  }
  else {
    Serial.print(F("=== Networks found: "));
    Serial.println(index);

    while (index) {
      index--;
      cc3000.getNextSSID(&rssi, &securityMode, ssid);

      Serial.print(F("\n=== SSID name    : "));
      Serial.println(ssid);
      Serial.print(F("=== RSSI         : "));
      Serial.println(rssi);
      Serial.print(F("=== Security mode: "));
      Serial.println(securityMode);
    }

    cc3000.stopSSIDscan();
    return true;
  }
}

bool connectToAccessPoint(Adafruit_CC3000 &cc3000, const char *ssid, const char *password, uint8_t securityMode, uint16_t dhcpTimeout) {
  Serial.print(F("=== Attempting to connect to "));
  Serial.print(ssid);
  Serial.println("...");
  if(!cc3000.connectToAP(ssid, password, securityMode)) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.println(F("=== Ok"));

    Serial.println(F("\n=== Waiting for DHCP to complete..."));
    uint16_t timer = dhcpTimeout;
    while ((timer > 0) && !cc3000.checkDHCP()) {
      delay(10);
      timer -= 10;
    }
    if (!cc3000.checkDHCP()) {
      Serial.println(F("=== Timed out!"));
      return false;
    }
    else {
      Serial.println(F("=== Ok"));
      return true;
    }
  }
}

bool displayConnectionDetails(Adafruit_CC3000 &cc3000) {
  uint32_t ipAddress, netmask, gateway, dhcpServer, dnsServer;

  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpServer, &dnsServer)) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.print(F("=== IP Address : "));
    cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\n=== Netmask    : "));
    cc3000.printIPdotsRev(netmask);
    Serial.print(F("\n=== Gateway    : "));
    cc3000.printIPdotsRev(gateway);
    Serial.print(F("\n=== DHCP server: "));
    cc3000.printIPdotsRev(dhcpServer);
    Serial.print(F("\n=== DNS server : "));
    cc3000.printIPdotsRev(dnsServer);
    Serial.println();
    return true;
  }
}

bool ping(Adafruit_CC3000 &cc3000, char *hostname, uint8_t attempts) {
  uint32_t ip;

  Serial.print(F("=== Resolving hostname '"));
  Serial.print(hostname);
  Serial.println(F("' ..."));
  if (!cc3000.getHostByName(hostname, &ip)) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.println(F("=== Ok"));

    Serial.print(F("\n=== Pinging "));
    cc3000.printIPdotsRev(ip);
    Serial.println(F("..."));
    uint8_t replies = cc3000.ping(ip, attempts, 1000);
    Serial.print(F("=== "));
    Serial.print(replies);
    Serial.println(F(" successful replies"));
    return true;
  }
}

bool disconnect(Adafruit_CC3000 &cc3000) {
  if (!cc3000.disconnect()) {
    Serial.println(F("=== Failed!"));
    return false;
  }
  else {
    Serial.println(F("=== Ok"));
    return true;
  }
}

bool displayStatus(Adafruit_CC3000 &cc3000) {
  Serial.print(F("=== Status   : "));
  Serial.println(cc3000.getStatus());
  Serial.print(F("=== Connected: "));
  Serial.println(cc3000.checkConnected());
  Serial.print(F("=== DHCP     : "));
  Serial.println(cc3000.checkDHCP());
  return true;
}
