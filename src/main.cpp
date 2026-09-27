#include <Arduino.h>

int buttonPin = 17;
int ledPin = 4;
bool lastButtonState = HIGH;

bool ledState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW)
  {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
  lastButtonState = buttonState;
  
  

}
