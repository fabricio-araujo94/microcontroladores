#include <Arduino.h>
#include <WiFi.h>
#include "ThingSpeak.h"

#define DELAY 500

#define LED_RED 22
#define POTENCIOMETER 34

#define SSID ""
#define PASSWORD ""

int potenciometer;
float tension;
int ledTension;

WiFiClient client;

unsigned long myChannelNumber = 1;
const char *myWriteAPIKey = "";

unsigned long lastTime = 0;
unsigned long timerDelay = 2500;

void setup()
{
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  pinMode(LED_RED, OUTPUT);
}

void loop()
{
  if ((millis() - lastTime) > timerDelay)
  {

    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Attempting to connect");
      while (WiFi.status() != WL_CONNECTED)
      {
        Serial.print(".");
        WiFi.begin(SSID, PASSWORD);
        delay(5000);
      }
      Serial.println("\nConnected.");
    }
    
    potenciometer = analogRead(POTENCIOMETER);
    Serial.print("Resolução:");
    Serial.println(potenciometer);

    // TENSION: 0 --- 3.3V
    // POTENCIOMETER: 0 --- 4095
    tension = potenciometer * (3.3 / 4095);
    Serial.print("Tensão:");
    Serial.println(tension);

    // LED: 0 --- 255
    // POTENCIOMETER: 0 --- 4095
    ledTension = potenciometer * (255.0 / 4095.0);
    analogWrite(LED_RED, ledTension);
    Serial.print("Tensão no Led: ");
    Serial.println(ledTension);

    int x = ThingSpeak.writeField(myChannelNumber, 1, tension, myWriteAPIKey);

    if (x == 200)
    {
      Serial.println("Channel update successful.");
    }
    else
    {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}