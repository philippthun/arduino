/*
  Robot

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
*/

#include "Robot.h"

const int PIN_RIGHT_BRAKE = 9;
const int PIN_RIGHT_DIRECTION = 12;
const int PIN_RIGHT_SPEED = 3;

const int PIN_LEFT_BRAKE = 8;
const int PIN_LEFT_DIRECTION = 13;
const int PIN_LEFT_SPEED = 11;

Robot::Robot() {
  pinMode(PIN_RIGHT_BRAKE, OUTPUT);
  pinMode(PIN_RIGHT_DIRECTION, OUTPUT);
  pinMode(PIN_RIGHT_SPEED, OUTPUT);

  pinMode(PIN_LEFT_BRAKE, OUTPUT);
  pinMode(PIN_LEFT_DIRECTION, OUTPUT);
  pinMode(PIN_LEFT_SPEED, OUTPUT);

  _brake();
}

void Robot::drive(boolean forward, int speed, int duration) {
  digitalWrite(PIN_RIGHT_BRAKE, LOW);
  digitalWrite(PIN_LEFT_BRAKE, LOW);

  if (forward) {
    digitalWrite(PIN_RIGHT_DIRECTION, LOW);
    digitalWrite(PIN_LEFT_DIRECTION, HIGH);
  }
  else {
    digitalWrite(PIN_RIGHT_DIRECTION, HIGH);
    digitalWrite(PIN_LEFT_DIRECTION, LOW);
  }

  analogWrite(PIN_RIGHT_SPEED, speed);
  analogWrite(PIN_LEFT_SPEED, speed);

  delay(duration);

  _brake();
}

void Robot::rotate(boolean clockwise, int speed, int duration) {
  digitalWrite(PIN_RIGHT_BRAKE, LOW);
  digitalWrite(PIN_LEFT_BRAKE, LOW);

  if (clockwise) {
    digitalWrite(PIN_RIGHT_DIRECTION, HIGH);
    digitalWrite(PIN_LEFT_DIRECTION, HIGH);
  }
  else {
    digitalWrite(PIN_RIGHT_DIRECTION, LOW);
    digitalWrite(PIN_LEFT_DIRECTION, LOW);
  }

  analogWrite(PIN_RIGHT_SPEED, speed);
  analogWrite(PIN_LEFT_SPEED, speed);

  delay(duration);

  _brake();
}

void Robot::_brake() {
  digitalWrite(PIN_RIGHT_BRAKE, HIGH);
  digitalWrite(PIN_LEFT_BRAKE, HIGH);

  analogWrite(PIN_RIGHT_SPEED, 0);
  analogWrite(PIN_LEFT_SPEED, 0);
}
