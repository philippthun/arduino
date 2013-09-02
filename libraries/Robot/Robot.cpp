/*
  Robot.cpp
*/

#include "Arduino.h"
#include "Robot.h"

const int PIN_RIGHT_BRAKE = 9;
const int PIN_RIGHT_DIRECTION = 12;
const int PIN_RIGHT_SPEED = 3;

const int PIN_LEFT_BRAKE = 8;
const int PIN_LEFT_DIRECTION = 13;
const int PIN_LEFT_SPEED = 11;

Robot::Robot()
{
  pinMode(PIN_RIGHT_BRAKE, OUTPUT);
  pinMode(PIN_RIGHT_DIRECTION, OUTPUT);
  pinMode(PIN_RIGHT_SPEED, OUTPUT);

  pinMode(PIN_LEFT_BRAKE, OUTPUT);
  pinMode(PIN_LEFT_DIRECTION, OUTPUT);
  pinMode(PIN_LEFT_SPEED, OUTPUT);

  _brake();
}

void Robot::drive(boolean forward, int speed, int duration)
{
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

void Robot::rotate(boolean clockwise, int speed, int duration)
{
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

void Robot::_brake()
{
  digitalWrite(PIN_RIGHT_BRAKE, HIGH);
  digitalWrite(PIN_LEFT_BRAKE, HIGH);

  analogWrite(PIN_RIGHT_SPEED, 0);
  analogWrite(PIN_LEFT_SPEED, 0);
}
