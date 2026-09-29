#include <Arduino.h>

int potPin = 34;
int whiteLedPin = 17;
int redLedPin = 19;
int buzzerPin = 21;

unsigned long previousTime = 0;
unsigned long interval = 500;

unsigned long previousSerial = 0;
unsigned long previousNormal = 0;
unsigned long previousWarning = 0;

bool buzzerState = LOW;

/* Declaration of States*/
enum States {
  NORMAL,
  WARNING,
  SYSTEM_FAILURE
};

States currentStates = NORMAL;

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);
  pinMode(whiteLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  int potValues = analogRead(potPin);

  /*Decision Block*/
  if (potValues < 1500)
  {
    currentStates = NORMAL;
  } else if (potValues >= 1500 && potValues < 3000)
  {
    currentStates = WARNING;
  }else if (potValues >= 3000)
  {
    currentStates = SYSTEM_FAILURE;
  }
  

  /*Action Block*/
  switch (currentStates)
  {
  case NORMAL:
    digitalWrite(whiteLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzerPin, LOW);
    if (currentMillis - previousNormal >= interval)
    {
      previousNormal = currentMillis;
      Serial.println("The System is Normal");
    }
    break;
  
  case WARNING:
    digitalWrite(whiteLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    if (currentMillis - previousWarning >= interval)
    {
      previousWarning = currentMillis;
      Serial.println("The System is Warning a danger");
    }
    break;
  
  case SYSTEM_FAILURE:
    digitalWrite(whiteLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    if (currentMillis - previousTime >= interval)
    {
      previousTime = currentMillis;
      buzzerState = !buzzerState;
      digitalWrite(buzzerPin, buzzerState);
      Serial.println("The System is in System Failure");
    }
    break;
  }

  if (currentMillis - previousSerial >= interval)
    {
      previousSerial = currentMillis;
      Serial.println(potValues);
    }
}

