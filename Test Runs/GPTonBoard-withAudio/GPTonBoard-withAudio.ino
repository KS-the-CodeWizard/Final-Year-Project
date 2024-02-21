
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <ArduinoJson.h>
#include "Audio.h"

const char* ssid = "Galaxy F22 E9F4";
const char* password = "KS1234321";
const char* chatgpt_token = "";
const char* temperature = "0";
const char* max_tokens = "30";
String Question = "";

#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

String extractContent(String jsonResponse) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, jsonResponse);
  JsonObject message = doc["choices"][0]["message"];
  return message["content"].as<String>();
}


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
  String greet ="Hello, Ask your question";
  output(greet);
}

void loop()
{
  
  Serial.print("Ask your Question : ");
  while (!Serial.available())
  {
    audio.loop();
  }
  while (Serial.available())
  {
    char add = Serial.read();
    Question = Question + add;
    delay(1);
  }
  int len = Question.length();
  Question = Question.substring(0, (len - 1));
  Question = "\"" + Question + "\"";
  Serial.println(Question);

  HTTPClient https;

   Serial.println("...");
    if (https.begin("https://api.openai.com/v1/chat/completions")) { 
      
      https.addHeader("Content-Type", "application/json"); 
      String token_key = String("Bearer ") + chatgpt_token;
      https.addHeader("Authorization", token_key);
      
      String payload = String("{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\":\"user\", \"content\": ")+ Question + String("}]") + String(", \"temperature\": ") + temperature + String(", \"max_tokens\": ") + max_tokens + String("}");; 
      
      //Serial.println(payload);
      int httpCode = https.POST(payload);
      Serial.println(payload);


    // httpCode will be negative on error
    // file found at server
      String payload2 = https.getString();
      Serial.println(payload2);

      String content = extractContent(payload2); 
      Serial.println(content);
      output(content);
      

    https.end();
  }
  else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  Question = "";
}

void output(String speech){
  audio.connecttospeech(speech.c_str(), "en");
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}
