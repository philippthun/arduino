/*
  Bluetooth test
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

