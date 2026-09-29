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





struct SystemNode {
  int btnPin;
  int indicatorPin;
  bool lastBtn;
  bool state;
  unsigned long timer;
};

SystemNode nodes[3] = {
  {17, 4, LOW, LOW, 0}, 
  {18, 5, HIGH, LOW, 0},
  {21, 19, HIGH, LOW, 0}
};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(nodes[i].btnPin, INPUT); 
    pinMode(nodes[i].indicatorPin, OUTPUT);
  }
}

void loop() {
  unsigned long now = millis();

  for (int i = 0; i < 2; i++) {
    bool currentBtn = digitalRead(nodes[i].btnPin);
    
    if (nodes[i].lastBtn == HIGH && currentBtn == HIGH) {
      if (now - nodes[i].timer >= 50) {
        nodes[i].state = !nodes[i].state;
        digitalWrite(nodes[i].indicatorPin, nodes[i].state);
      }
    }
    nodes[i].lastBtn = currentBtn;
  }

  for (int i = 0; i < 3; i++)
  {
    bool EBtnState = digitalRead(nodes[2].btnPin);
    if (nodes[2].lastBtn == HIGH && EBtnState == LOW)
    {
      if (now - nodes[2].timer >= 50)
      {
        nodes[2].timer = now;
        nodes[i].state = LOW;
        digitalWrite(nodes[i].indicatorPin, nodes[i].state);
      }
    }
    nodes[2].lastBtn = EBtnState;
  } 
}