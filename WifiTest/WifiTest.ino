/*
  Wifi test
 */

#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <Adafruit_CC3000_Helper.h>
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
    initWifiModule(cc3000);
    resetCommand();
  }
  else if (commandAction == 'b') {
    Serial.println(F("\n=== Checking firmware version..."));
    checkFirmwareVersion(cc3000);
    resetCommand();
  }
  else if (commandAction == 'c') {
    Serial.println(F("\n=== Displaying MAC address..."));
    displayMacAddress(cc3000);
    resetCommand();
  }
  else if (commandAction == 'd') {
    Serial.println(F("\n=== Listing networks..."));
    listNetworks(cc3000);
    resetCommand();
  }
  else if (commandAction == 'e') {
    Serial.println(F("\n=== Connecting to access point..."));
    connectToAccessPoint(cc3000, WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
    resetCommand();
  }
  else if (commandAction == 'f') {
    Serial.println(F("\n=== Displaying connection details..."));
    displayConnectionDetails(cc3000);
    resetCommand();
  }
  else if (commandAction == 'g') {
    Serial.println(F("\n=== Pinging Google..."));
    ping(cc3000, "www.google.com", 5);
    resetCommand();
  }
  else if (commandAction == 'h') {
    Serial.println(F("\n=== Disconnecting..."));
    disconnect(cc3000);
    resetCommand();
  }
  else if (commandAction == 'i') {
    Serial.println(F("\n=== Displaying status..."));
    displayStatus(cc3000);
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
  Serial.println(F(" e - Connect to access point"));
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

