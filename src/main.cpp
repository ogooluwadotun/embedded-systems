#include <Arduino.h>

struct ControlNodes
{
  int buttonPin;
  int ledPin;
  bool lastButtonState;
  bool ledState;
  unsigned long lastDebounceTime;
};

const int totalButtons = 3;

ControlNodes myNodes[totalButtons] = {
  {4, 17, HIGH, LOW, 0},
  {5, 18, HIGH, LOW, 0},
  {21, 19, HIGH, LOW, 0}
};

unsigned long threshold = 50;

void setup() {
  Serial.begin(115200);
for (int i = 0; i < totalButtons; i++)
{
  pinMode(myNodes[i].ledPin, OUTPUT);
  pinMode(myNodes[i].buttonPin, INPUT_PULLUP);
}

}

void loop() {

  unsigned long currentMillis = millis();

  for (int i = 0; i < totalButtons; i++)
  {
    bool buttonState = digitalRead(myNodes[i].buttonPin);

    if (myNodes[i].lastButtonState == HIGH && buttonState == LOW)
    {
      if (currentMillis - myNodes[i].lastDebounceTime >= threshold)
      {
        myNodes[i].lastDebounceTime = currentMillis;
        myNodes[i].ledState = !myNodes[i].ledState;
        digitalWrite(myNodes[i].ledPin, myNodes[i].ledState);
      }
    }
    myNodes[i].lastButtonState =  buttonState;
  }
  

}

