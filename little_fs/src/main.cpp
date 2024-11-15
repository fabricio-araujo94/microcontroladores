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
void listDir(fs::FS &);
void listDirAux(fs::FS &, const char *, uint8_t);

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

void listDir(fs::FS &fs){
  listDirAux(fs, "/", 1);
}

void listDirAux(fs::FS &fs, const char *dirname, uint8_t levels){
    Serial.printf("Directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed!");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory.");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDirAux(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}