#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <vector>

using namespace std;

#define RED 21
#define GREEN 19
#define BLUE 18

#define SSID ""
#define PASSWORD ""

// put function declarations here:
bool createDir(fs::FS &, const char *);
void listDir(fs::FS &);
void listDirAux(fs::FS &, const char *, uint8_t);
void writeFile(fs::FS &, const char *, const char *);
vector<String> readFile(fs::FS &, const char *);
void deleteFile(fs::FS &, const char *);

void setup()
{
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  if (!LittleFS.begin(true))
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  // create dirs
  createDir(LittleFS, "/wifi");
  createDir(LittleFS, "/rgb_state");

  // writing files
  String credentials = String(SSID) + "," + String(PASSWORD);
  String states = "HIGH,LOW,HIGH";

  writeFile(LittleFS, "/wifi/credentials.txt", credentials.c_str());
  writeFile(LittleFS, "/rgb_state/states.txt", states.c_str());

  // read files
  vector<String> wifi_creds = readFile(LittleFS, "/wifi/credentials.txt");
  vector<String> rgbs = readFile(LittleFS, "/rgb_state/states.txt");

  // setting wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_creds.at(0), wifi_creds.at(1));

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // setting rgbs
  if (rgbs.at(0) == "HIGH")
  {
    digitalWrite(RED, HIGH);
  }
  else
  {
    digitalWrite(RED, LOW);
  }

  if (rgbs.at(1) == "HIGH")
  {
    digitalWrite(GREEN, HIGH);
  }
  else
  {
    digitalWrite(GREEN, LOW);
  }

  if (rgbs.at(2) == "HIGH")
  {
    digitalWrite(BLUE, HIGH);
  }
  else
  {
    digitalWrite(BLUE, LOW);
  }

  LittleFS.end();
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

void listDir(fs::FS &fs)
{
  listDirAux(fs, "/", 1);
}

void listDirAux(fs::FS &fs, const char *dirname, uint8_t levels)
{
  Serial.printf("Directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("Failed!");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println("Not a directory.");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels)
      {
        listDirAux(fs, file.path(), levels - 1);
      }
    }
    else
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing in: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed!");
    return;
  }
  if (file.print(message))
  {
    Serial.println("Done!");
  }
  else
  {
    Serial.println("Something wrong happened. Failed!");
  }
  file.close();
}

vector<String> readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    Serial.println("Failed to open. Check the path.");
    return;
  }

  String content = "";

  while (file.available())
  {
    content += (char)file.read();
  }

  Serial.println("Content: \n" + content);

  file.close();

  return splitString(content, ",");
}

vector<String> splitString(String text, String delimiter)
{
  vector<String> words;

  int start = 0;
  int end;

  while ((end = text.indexOf(delimiter, start)) != -1)
  {
    String word = text.substring(start, end);
    words.push_back(word);
    start = end + delimiter.length();
  }

  String lastWord = text.substring(start);
  if (lastWord.length() > 0)
  {
    words.push_back(lastWord);
  }

  for (const auto &str : words)
  {
    Serial.println(str);
  }

  return words;
}

void deleteFile(fs::FS &fs, const char *path)
{
  Serial.printf("Deleting file: %s\r\n", path);
  if (fs.remove(path))
  {
    Serial.println("File deleted.");
  }
  else
  {
    Serial.println("Delete failed!");
  }
}