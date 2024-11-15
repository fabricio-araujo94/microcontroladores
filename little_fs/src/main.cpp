#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
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

vector<String> splitString(String text, String delimiter) {
  vector<String> words;  // Vetor para armazenar as palavras divididas

  int start = 0;
  int end;

  // Encontrar as palavras divididas pelo delimitador
  while ((end = text.indexOf(delimiter, start)) != -1) {
    String word = text.substring(start, end);  // Pega a palavra entre os índices start e end
    words.push_back(word);  // Adiciona a palavra ao vetor
    start = end + delimiter.length();  // Move o índice de início para após o delimitador
  }

  String lastWord = text.substring(start);
  if (lastWord.length() > 0) {
    words.push_back(lastWord);  
  }

  for (const auto &str : words) {
    Serial.println(str);
  }

  return words;
}
