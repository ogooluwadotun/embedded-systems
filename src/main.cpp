#include <Arduino.h>

const int totalButtons = 3;

int buttonPins[totalButtons] = {4, 5, 21};
int ledPins[totalButtons]    = {17, 18, 19};

bool lastButtonStates[totalButtons] = {HIGH, HIGH, HIGH};
bool ledStates[totalButtons]        = {LOW, LOW, LOW};
unsigned long lastDebounceTimes[totalButtons] = {0, 0, 0};
unsigned long threshold = 50;

void setup() {
  Serial.begin(115200);
for (int i = 0; i < totalButtons; i++)
{
  pinMode(ledPins[i], OUTPUT);
  pinMode(buttonPins[i], INPUT_PULLUP);
}

}

void loop() {

  unsigned long currentMillis = millis();

  for (int i = 0; i < totalButtons; i++)
  {
    bool buttonState = digitalRead(buttonPins[i]);

    if (lastButtonStates[i] == HIGH && buttonState == LOW)
    {
      if (currentMillis - lastDebounceTimes[i] >= threshold)
      {
        lastDebounceTimes[i] = currentMillis;
        ledStates[i] = !ledStates[i];
      digitalWrite(ledPins[i], ledStates[i]);
      }
    }
    lastButtonStates[i] =  buttonState;
  }
  

}
