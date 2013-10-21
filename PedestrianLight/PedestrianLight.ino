/*
  Pedestrian light

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

const int carRedPin = 12;
const int carYellowPin = 11;
const int carGreenPin = 10;
const int pedRedPin = 9;
const int pedGreenPin = 8;
const int pedWaitPin = 13;
const int buttonPin = 2;

unsigned long time;
int buttonState;
int lightState = 0;
boolean pedPushed = false;
unsigned long waitUntil = 0;

int carRedState = LOW;
int carYellowState = LOW;
int carGreenState = HIGH;
int pedRedState = HIGH;
int pedGreenState = LOW;
int pedWaitState = LOW;

void setup() {
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(pedGreenPin, OUTPUT);
  pinMode(pedWaitPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  time = millis();
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && (lightState == 0 || lightState >= 5)) {
    pedPushed = true;
    pedWaitState = HIGH;
  }

  switch (lightState) {
  case 0:
    if (pedPushed == true) {
      pedPushed = false;
      if (waitUntil == 0 || waitUntil < time + 5000) {
        waitUntil = time + 5000;
      }
      lightState++;
    }
    break;
  case 1:
    if (time > waitUntil) {
      carYellowState = HIGH;
      carGreenState = LOW;
      waitUntil = time + 2000;
      lightState++;
    }
    break;
  case 2:
    if (time > waitUntil) {
      carRedState = HIGH;
      carYellowState = LOW;
      waitUntil = time + 2000;
      lightState++;
    }
    break;
  case 3:
    if (time > waitUntil) {
      pedRedState = LOW;
      pedGreenState = HIGH;
      pedWaitState = LOW;
      waitUntil = time + 10000;
      lightState++;
    }
    break;
  case 4:
    if (time > waitUntil) {
      pedRedState = HIGH;
      pedGreenState = LOW;
      waitUntil = time + 2000;
      lightState++;
    }
    break;
  case 5:
    if (time > waitUntil) {
      carYellowState = HIGH;
      waitUntil = time + 2000;
      lightState++;
    }
    break;
  case 6:
    if (time > waitUntil) {
      carRedState = LOW;
      carYellowState = LOW;
      carGreenState = HIGH;
      waitUntil = time + 20000;
      lightState = 0;
    }
    break;
  }

  digitalWrite(carRedPin, carRedState);
  digitalWrite(carYellowPin, carYellowState);
  digitalWrite(carGreenPin, carGreenState);
  digitalWrite(pedRedPin, pedRedState);
  digitalWrite(pedGreenPin, pedGreenState);
  digitalWrite(pedWaitPin, pedWaitState);

  delay(50);
}

