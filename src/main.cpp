#include <Arduino.h>

int whiteLed = 17;
int redLed = 5;
int greenLed = 18;
int potPin = 34;

unsigned long previousMillis = 0;
unsigned long previousSerial = 0;
unsigned long interval = 250;

bool redLedState = LOW;

/*Declaration Block*/

enum State {
  LOW_VOLTAGE_FAULT,
  BULK_CHARGING,
  FLOAT_CHARGING
};

State currentState = FLOAT_CHARGING;

void setup() {
  Serial.begin(115200);
  pinMode(whiteLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {

  unsigned long currentMillis = millis();

  int potValue = analogRead(potPin);

  /*Decision Block*/
  if (potValue <= 1200)
  {
    currentState = LOW_VOLTAGE_FAULT;
  } else if (potValue > 1200 && potValue <= 3800)
  {
    currentState = BULK_CHARGING;
  } else if (potValue > 3800)
  {
    currentState = FLOAT_CHARGING;
  }
  

  switch (currentState)
  {
  case FLOAT_CHARGING :
    digitalWrite(redLed, LOW);
    digitalWrite(whiteLed, LOW);
    digitalWrite(greenLed, HIGH);
    break;
  
  case BULK_CHARGING:
    digitalWrite(redLed, LOW);
    digitalWrite(whiteLed, HIGH);
    digitalWrite(greenLed, LOW);
    break;

    case LOW_VOLTAGE_FAULT:
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      redLedState = !redLedState;
      digitalWrite(redLed, redLedState);
    }
    digitalWrite(whiteLed, LOW);
    digitalWrite(greenLed, LOW);
    break;
  }
  
  if (currentMillis - previousSerial >= interval)
  {
    previousSerial = currentMillis;
    Serial.println(potValue);
  }
  
  
  

}

