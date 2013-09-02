/*
  Robot.h
*/

#ifndef Robot_h
#define Robot_h

#include "Arduino.h"

class Robot
{
  public:
    Robot();
    void drive(boolean forward, int speed, int duration);
    void rotate(boolean clockwise, int speed, int duration);
  private:
    void _brake();
};

#endif
