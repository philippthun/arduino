/*
  Button switches LED state
 */

const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int ledState = LOW;
boolean changed = false;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    if (changed == false) {
      if (ledState == HIGH) {
        ledState = LOW;
      } 
      else {
        ledState = HIGH;
      }
      digitalWrite(ledPin, ledState);
      changed = true;
    }
  } 
  else {
    if (changed == true) {
      changed = false;
    }
  }
}

