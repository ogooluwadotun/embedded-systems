#include <Arduino.h>

int potPin = 34;
int ledPin = 17;
int threshold = 3000;

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int values = analogRead(potPin);
  delay(100);
  
  if (values >= 3000)
  {
    digitalWrite(ledPin, HIGH);
    Serial.print(values);
    Serial.print("  ");
    Serial.println("It is Night");
  }else
  {
    digitalWrite(ledPin, LOW);
    Serial.print(values);
    Serial.print("  ");
    Serial.println("It is Day");
  }
  

  

}

