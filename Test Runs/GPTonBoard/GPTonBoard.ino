#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Galaxy F22 E9F4";
const char* password = "KS1234321";
const char* chatgpt_token = "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";
char chatgpt_Q[256];

String extractContent(String jsonResponse) {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, jsonResponse);
  JsonObject message = doc["choices"][0]["message"];
  return message["content"].as<String>();
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while(!Serial);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected, Now enter your question:-->");
}

void loop() {
  while (!Serial.available()) {
    delay(100);
  }
  String input = Serial.readStringUntil('\n');

  input.trim();
  input.toCharArray(chatgpt_Q, sizeof(chatgpt_Q));
  Serial.println(chatgpt_Q);

    HTTPClient https;

    Serial.println("...");
    if (https.begin("https://api.openai.com/v1/chat/completions")) { 
      
      https.addHeader("Content-Type", "application/json"); 
      String token_key = String("Bearer ") + chatgpt_token;
      https.addHeader("Authorization", token_key);
      
      String payload = String("{\"model\": \"gpt-3.5-turbo\", \"messages\": [{\"role\":\"user\", \"content\": \"")+ chatgpt_Q + String("\"}]}"); 
      
      //Serial.println(payload);
      int httpCode = https.POST(payload);

      String payload2 = https.getString();
      String content = extractContent(payload2); 
      Serial.println(content);

      https.end();
    }

  Serial.println("----------------");
  delay(1000);
}
