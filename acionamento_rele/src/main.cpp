#include <Arduino.h>
#include <Wifi.h>
#include <WifiClientSecure.h>
#include <UniversalTelegramBot.h>

// pins
#define RELE 23

// network credential
#define SSID ""
#define PASSWORD ""

// telegram bot
#define BOTTOKEN ""

// your chat id
#define CHATID ""

// put function declarations here:

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(RELE, OUTPUT);
  digitalWrite(RELE, LOW);

  // Connecting to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here: