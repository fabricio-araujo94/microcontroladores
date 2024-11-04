#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// network credential
#define SSID ""
#define PASSWORD ""

// telegram bot
#define BOTTOKEN ""

// your chat id
#define CHATID ""

// pins
#define BUTTON 19
#define CAR_LED_RED 21
#define CAR_LED_GREEN 22
#define CAR_LED_BLUE 23
#define PEDESTRIAN_LED_RED 33
#define PEDESTRIAN_LED_GREEN 32
#define PEDESTRIAN_LED_BLUE 26

// time of wait
#define SLEEP 5000
#define ATTENTION 2000

// tasks
TaskHandle_t Task1;
TaskHandle_t Task2;

// global
WiFiClientSecure client;

// put function declarations here:
void carRun();
void carAttention();
void pedestrianRun();
void pedestrianAttention();

void semaphore(void *);
void triggering(void *);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(CAR_LED_RED, OUTPUT);
  pinMode(CAR_LED_GREEN, OUTPUT);
  pinMode(CAR_LED_BLUE, OUTPUT);
  pinMode(PEDESTRIAN_LED_RED, OUTPUT);
  pinMode(PEDESTRIAN_LED_GREEN, OUTPUT);
  pinMode(PEDESTRIAN_LED_BLUE, OUTPUT);
  pinMode(BUTTON, INPUT_PULLDOWN);
  digitalWrite(BUTTON, LOW);

  
  // Connecting to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  xTaskCreatePinnedToCore(semaphore, "Semaphore", 10000, NULL, 0, &Task1, 0);
  xTaskCreatePinnedToCore(triggering, "Triggering",  10000, NULL, 1, &Task2, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

// functions for threads
void semaphore(void *parameter) {
  if(digitalRead(BUTTON) == HIGH) {
    Serial.println("Semáforo acionado!");
    carAttention();
    pedestrianRun();
    pedestrianAttention();
  } else {
    carRun();
  }
  delay(500);
}

void triggering(void *parameter) {
  if(digitalRead(BUTTON) == HIGH) {
    Serial.println("Mensagem enviada!");
  }
  delay(750);
}


// put function definitions here:
void carRun() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, HIGH);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, HIGH);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
}

void carAttention() {
  digitalWrite(CAR_LED_RED, LOW);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, HIGH);
  digitalWrite(PEDESTRIAN_LED_RED, HIGH);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
  delay(ATTENTION);
};

void pedestrianRun() {
  digitalWrite(CAR_LED_RED, HIGH);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, LOW);
  digitalWrite(PEDESTRIAN_LED_GREEN, HIGH);
  digitalWrite(PEDESTRIAN_LED_BLUE, LOW);
  delay(SLEEP);
};

void pedestrianAttention() {
  digitalWrite(CAR_LED_RED, HIGH);
  digitalWrite(CAR_LED_GREEN, LOW);
  digitalWrite(CAR_LED_BLUE, LOW);
  digitalWrite(PEDESTRIAN_LED_RED, LOW);
  digitalWrite(PEDESTRIAN_LED_GREEN, LOW);
  digitalWrite(PEDESTRIAN_LED_BLUE, HIGH);
  delay(ATTENTION);
};
