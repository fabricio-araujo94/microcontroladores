#include <Arduino.h>
#define LED 18
#define SLEEP 1000

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(SLEEP);
  digitalWrite(LED, LOW);
  delay(SLEEP);
}
