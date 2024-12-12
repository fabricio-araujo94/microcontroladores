#include <Arduino.h>

#define TRIG 5
#define ECHO 18
#define RED 19
#define GREEN 21

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(TRIG, LOW);
  delayMicroseconds(20);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(100);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distanceCm = duration * SOUND_SPEED / 2;

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  if(distanceCm <= 10) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  } else if (distanceCm > 10 && distanceCm < 20) {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
  } else {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  }

  delay(2000);
}

// put function definitions here: