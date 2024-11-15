#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

#define RED 21
#define GREEN 19
#define BLUE 18

#define SSID ""
#define PASSWORD ""

// put function declarations here:
bool createDir(fs::FS &, const char *);

void setup()
{
  // put your setup code here, to run once:

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
bool createDir(fs::FS &fs, const char *path)
{
  Serial.printf("Creating Dir: %s... ", path);
  if (fs.mkdir(path))
  {
    Serial.println("Done!");
    return true;
  }
  else
  {
    Serial.println("Failed!");
    return false;
  }
}