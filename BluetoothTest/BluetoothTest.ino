/*
  Bluetooth test

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

const int LED_PIN = 7;

char buffer[64];
int length;

int commandDuration;

void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  resetCommand();
}

void loop() {
  if (Serial.available() > 0) {
    receiveCommand();
  }

  if (commandDuration != 0) {
    digitalWrite(LED_PIN, HIGH);
    delay(commandDuration);
    digitalWrite(LED_PIN, LOW);
    resetCommand();
  } 

  delay(50);
}

void resetCommand() {
  commandDuration = 0;
}

void receiveCommand() {
  length = Serial.readBytesUntil('.', buffer, 64);

  commandDuration = 0;
  for (int i = 0; i < length; i++) {
    if (buffer[i] >= '0' && buffer[i] <= '9') {
      commandDuration *= 10;
      commandDuration += buffer[i] - '0';
    } 
    else {
      Serial.println("Illegal duration.");
      return;
    }
  }

  Serial.print("Command received: ");
  Serial.print("duration=");
  Serial.print(commandDuration);
  Serial.println(".");
}

