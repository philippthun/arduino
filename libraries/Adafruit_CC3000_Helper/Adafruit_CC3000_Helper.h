/*
  Adafruit CC3000 Helper

  Reusable helper functions for the Adafruit CC3000 library (https://github.com/
  adafruit/Adafruit_CC3000_Library). Most functions have been taken from or are
  inspired by the library's examples - see below for additional information.

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

#ifndef Adafruit_CC3000_Helper_h
#define Adafruit_CC3000_Helper_h

#include "Adafruit_CC3000.h"

bool initWifiModule(Adafruit_CC3000 &cc3000);
bool checkFirmwareVersion(Adafruit_CC3000 &cc3000);
bool displayMacAddress(Adafruit_CC3000 &cc3000);
bool listNetworks(Adafruit_CC3000 &cc3000);
bool connectToAccessPoint(Adafruit_CC3000 &cc3000, const char *ssid, const char *password, uint8_t securityMode, uint16_t dhcpTimeout = 10000);
bool displayConnectionDetails(Adafruit_CC3000 &cc3000);
bool ping(Adafruit_CC3000 &cc3000, char *hostname, uint8_t attempts);
bool disconnect(Adafruit_CC3000 &cc3000);
bool displayStatus(Adafruit_CC3000 &cc3000);

#endif
