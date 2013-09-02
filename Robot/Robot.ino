/*
  Robot
 */

#include <Robot.h>

const int SLOW = 142; // +/- 10% => 128 -> 156
const int FAST = 232; // +/- 10% => 209 -> 255

Robot robot;

char buffer[64];
int length;

char commandAction;
char commandDirection;
char commandSpeed;
int commandDuration;

void setup() {
  Serial.begin(115200);

  resetCommand();
}

void loop() {
  if (Serial.available() > 0) {
    receiveCommand();
  }

  if (commandAction == 'd') {
    int drivingSpeed = SLOW;
    if (commandSpeed == 'f') {
      drivingSpeed = FAST;
    }
    boolean forward = true;
    if (commandDirection == '-') {
      forward = false;
    }
    robot.drive(forward, drivingSpeed, commandDuration);
    resetCommand();
  } 
  else if (commandAction == 'r') {
    int rotatingSpeed = SLOW;
    if (commandSpeed == 'f') {
      rotatingSpeed = FAST;
    }
    boolean clockwise = true;
    if (commandDirection == '-') {
      clockwise = false;
    }
    robot.rotate(clockwise, rotatingSpeed, commandDuration);
    resetCommand();
  }

  delay(50);
}

void resetCommand() {
  commandAction = ' ';
  commandDirection = ' ';
  commandSpeed = ' ';
  commandDuration = 0;
}

void receiveCommand() {
  length = Serial.readBytesUntil('.', buffer, 64);

  commandAction = buffer[0];
  if (commandAction != 'd' && commandAction != 'r') {
    Serial.println("Illegal action.");
    return;
  }

  commandDirection = buffer[1];
  if (commandDirection != '+' && commandDirection != '-') {
    Serial.println("Illegal direction.");
    return;
  }

  commandSpeed = buffer[2];
  if (commandSpeed != 's' && commandSpeed != 'f') {
    Serial.println("Illegal speed.");
    return;
  }

  commandDuration = 0;
  for (int i = 3; i < length; i++) {
    if (buffer[i] >= '0' && buffer[i] <= '9') {
      commandDuration *= 10;
      commandDuration += buffer[i] - '0';
    } 
    else {
      Serial.println("Illegal duration.");
      return;
    }
  }

  //Serial.print("Command received: ");
  //Serial.print("action=");
  //Serial.print(commandAction);
  //Serial.print(", direction=");
  //Serial.print(commandDirection);
  //Serial.print(", speed=");
  //Serial.print(commandSpeed);
  //Serial.print(", duration=");
  //Serial.print(commandDuration);
  //Serial.println(".");
}

