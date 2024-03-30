
#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
};

MyData data;

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
  Wire.begin();
  mpu.initialize();
  pinMode(LED_BUILTIN, OUTPUT);

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
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255);  // Y axis data
  delay(500);
  Serial.print("Axis X = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Axis Y = ");
  Serial.println(data.Y);

  String gesture = detectGesture(data.Y);
  String textCommand = mapGestureToTextCommand(gesture);
  convertTextToSpeech(textCommand);
}
//--------------------------------------------
//--------------------------------------------
void loop()
{
  audio.loop();
}
//-------------------------------------------
//-------------------------------------------
String detectGesture(float gyroY) {
  if (gyroY < 80) { //gesture : left 
    return ("gesture1");
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (gyroY > 145) {//gesture : right
    digitalWrite(LED_BUILTIN, HIGH);
    return ("gesture2");
  }
  if (gyroY > 80 && gyroY < 145) {//gesture : center
    return ("gesture3");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
  }
  else{
    return "No gesture detected";
  }
}

String mapGestureToTextCommand(String gesture) {
    if (gesture == "gesture1") {
        return "Turn on the lights";
    } else if (gesture == "gesture2") {
        return "Play music";
    } else if (gesture == "gesture3") {
        return "Madarchod";
    }
    else{
      return "Unknown gesture";
    }
}

void convertTextToSpeech(String speech){
  audio.connecttospeech(speech.c_str(), "en");
}

void audio_info(const char *info) {
  Serial.print("audio_info: "); Serial.println(info);
}