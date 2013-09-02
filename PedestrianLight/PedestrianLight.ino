/*
  Pedestrian light
 */

const int carRedPin = 13;
const int carYellowPin = 12;
const int carGreenPin = 8;
const int pedRedPin = 7;
const int pedGreenPin = 4;
const int buttonPin = 2;

int carRedState = 0;
int carYellowState = 0;
int carGreenState = 0;
int pedRedState = 0;
int pedGreenState = 0;

unsigned long time = 0;
int buttonState = 0;
boolean pedPushed = false;
boolean pedHasGreen = false;
unsigned long waitUntil = 0;
int switchStep = 0;

void setup() {
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(pedGreenPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  carRedState = LOW;
  carYellowState = LOW;
  carGreenState = HIGH;
  pedRedState = HIGH;
  pedGreenState = LOW;
}

void loop() {
  time = millis();
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && pedPushed == false && pedHasGreen == false) {
    pedPushed = true;
    if (waitUntil == 0 || waitUntil < time + 5000) {
      waitUntil = time + 5000;
    }
  }

  if (pedPushed == true && time > waitUntil) {
    switch (switchStep) {
    case 0:
      carYellowState = HIGH;
      carGreenState = LOW;
      waitUntil = time + 2000;
      switchStep++;
      break;
    case 1:
      carRedState = HIGH;
      carYellowState = LOW;
      waitUntil = time + 2000;
      switchStep++;
      break;
    case 2:
      pedRedState = LOW;
      pedGreenState = HIGH;
      switchStep = 0;
      pedPushed = false;
      pedHasGreen = true;
      waitUntil = time + 10000;
      break;
    }
  }

  if (pedHasGreen == true && time > waitUntil) {
    switch (switchStep) {
    case 0:
      pedRedState = HIGH;
      pedGreenState = LOW;
      waitUntil = time + 2000;
      switchStep++;
      break;
    case 1:
      carYellowState = HIGH;
      waitUntil = time + 2000;
      switchStep++;
      break;
    case 2:
      carRedState = LOW;
      carYellowState = LOW;
      carGreenState = HIGH;
      switchStep = 0;
      pedHasGreen = false;
      waitUntil = time + 20000;
      break;
    }
  }

  digitalWrite(carRedPin, carRedState);
  digitalWrite(carYellowPin, carYellowState);
  digitalWrite(carGreenPin, carGreenState);
  digitalWrite(pedRedPin, pedRedState);
  digitalWrite(pedGreenPin, pedGreenState);
}

