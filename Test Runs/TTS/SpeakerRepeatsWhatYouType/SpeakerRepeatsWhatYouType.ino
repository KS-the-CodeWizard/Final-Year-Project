
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <ArduinoJson.h>
#include "Audio.h"

const char* ssid = "Galaxy F22 E9F4";
const char* password = "KS1234321";
String Question = "";

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();


  while (!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  String greet ="Type in serial monitor, I will repeat...";
  output(greet);
}

void loop()
{
  while (!Serial.available())
  {
    audio.loop();
  }  while (Serial.available())
  {
    char add = Serial.read();
    Question = Question + add;
    output(Question);
    delay(1);
  }
 Question="";
}

void output(String speech){
  audio.connecttospeech(speech.c_str(), "en");
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
