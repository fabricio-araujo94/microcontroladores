#include <Arduino.h>

#define RED 18
#define GREEN 19
#define BLUE 21

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // yellow
  analogWrite(RED, 255);
  analogWrite(GREEN, 255);
  analogWrite(BLUE, 0);
  delay(3000);

  // purple
  analogWrite(RED, 158);
  analogWrite(GREEN, 10);
  analogWrite(BLUE, 149);
  delay(3000);

  // orange
  analogWrite(RED, 251);
  analogWrite(GREEN, 64);
  analogWrite(BLUE, 3);
  delay(3000);
}

// put function definitions here:
