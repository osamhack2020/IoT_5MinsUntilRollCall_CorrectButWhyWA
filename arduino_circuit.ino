#include <Servo.h>
Servo sv;

int state;
const int STATE_OPENED = 48;
const int STATE_CLOSED = 49;

const int motorPin = 9;
const int checkPin = 2;
const int ledPin = 4;

void setup() {
  Serial.begin(9600);
  sv.attach(motorPin);
  sv.write(0);
  state = STATE_OPENED;
  
  pinMode(checkPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int connected = digitalRead(checkPin);
  
  digitalWrite(ledPin, connected);
  
  if(Serial.available() > 0) {
    int read = Serial.read();
    if(connected == HIGH) {
      if(read != state) {
        if(read == STATE_CLOSED) {
          Serial.println("Close the Box!");
          for(int i = 0; i < 180; i++) {
            sv.write(i);
            delay(10);
          }
        }
        else if(read == STATE_OPENED) {
          Serial.println("Open the Box!");
          for(int i = 180; i > 0; i--) {
            sv.write(i);
            delay(10);
          }
        }
        state = read;
      }
    }
  }
}
  