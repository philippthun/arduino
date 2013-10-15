/*
  Adafruit CC3000 Helper

  Reusable helper functions for the Adafruit CC3000 library
  (https://github.com/adafruit/Adafruit_CC3000_Library). Most functions have been taken from or are
  inspired by the library's examples.
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
