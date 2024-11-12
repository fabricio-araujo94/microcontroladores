#include <Arduino.h>

#define LED 25
#define DELAY 3000
#define THRESHOLD 40 // the smaller it is, the more sensitive it is.


void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}