#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawInformations();

void setup() {
  Serial.begin(9600);

  delay(250); 

  display.begin(i2c_Address, true); 

  display.display();

  delay(2000);

  display.clearDisplay();
}

void loop() {
  drawInformations();
}

void drawInformations(){
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Temperatura: ");
  display.print("32");
  display.print((char) 247);
  display.print("C");
  display.display();
  delay(4000);
  display.clearDisplay();

  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Umidade: ");
  display.println("72%");
  display.display();
  delay(4000);
  display.clearDisplay();

  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Chovendo: ");
  display.println("Sim");

  display.setTextSize(1);
  display.println("Janelas fechadas");
  display.println("Varal recolhido");
  display.display();
  delay(4000);
  display.clearDisplay();
}