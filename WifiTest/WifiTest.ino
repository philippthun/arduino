/*
  Wifi test

  Based on examples from the Adafruit CC3000 library (https://github.com/adafruit/
  Adafruit_CC3000_Library) - see below for additional information.

  --------------------------------------------------------------------------------
  Copyright (c) 2013 Philipp Thun

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  --------------------------------------------------------------------------------
  Additional copyright / license information:

  Written by Adafruit Industries, distributed under BSD License.

  Designed specifically to work with the Adafruit WiFi products:
  ----> https://www.adafruit.com/products/1469

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  --------------------------------------------------------------------------------
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

