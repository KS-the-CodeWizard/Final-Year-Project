#include <Arduino.h>
#include <WiFi.h>
#include <Audio.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRC  26

Adafruit_MPU6050 Gyro;// Initialize MPU6050 and Audio objects
Audio audio;

void setup() {

    Serial.begin(115200);

    // Initialize MPU6050
    if(!Gyro.begin()){
      while(1){
        Serial.println("Gyro.NOT.Ready!!");
        delay(20);
      }Serial.println("Gyro..Ready");
    }

    //Connect to WIFI
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin( "SSID", "PASSWORD");
    while (WiFi.status() != WL_CONNECTED)
    delay(1500);

    // Initialize Audio
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(100);
    audio.connecttospeech("Your device is ready...", "en"); // Google TTS
}

void loop() {

    //Function defined here
    String detectGesture(int flexSensor1,int flexSensor2,int flexSensor3,int flexSensor4, int gyroX, int gyroY, int gyroZ);
    String mapGestureToTextCommand(String gesture);
    void convertTextToSpeech(String textCommand);

    // Read sensor data
    int flexSensor1 = analogRead(1);
    int flexSensor2 = analogRead(2);
    int flexSensor3 = analogRead(3);
    int flexSensor4 = analogRead(4);

    sensors_event_t acc, gcc, temp;
    Gyro.getEvent(&acc,&gcc,&temp);
    // Serial.println((gcc.gyro.x));
    int gyroX = gcc.gyro.x;
    int gyroY = gcc.gyro.y;
    int gyroZ = gcc.gyro.z;

    // Detect hand gesture based on sensor data
    String gesture = detectGesture(flexSensor1,flexSensor2,flexSensor3,flexSensor4, gyroX, gyroY, gyroZ);

    // Map gesture to text command
    String textCommand = mapGestureToTextCommand(gesture);

    // Convert text command to speech
    convertTextToSpeech(textCommand);

    // Add delay or other logic as needed
    delay(1000);
}

String detectGesture(int flexSensor1,int flexSensor2,int flexSensor3,int flexSensor4, int gyroX, int gyroY, int gyroZ) {
    // Implement gesture detection algorithm
    // Return detected gesture as a String
    // if (flexSensor1 > x && gyroX > y) {
    //     return "Gesture1";
    // } else if (flexSensorV2 < x2 && gyroY > y2) {
    //     return "Gesture2";
    // } else if (gyroZ < z) {
    //     return "Gesture3";
    // }
    // Add more gesture detection logic as needed
    return "No gesture detected";
}

String mapGestureToTextCommand(String gesture) {
    // Implement mapping between gestures and text commands
    // Return corresponding text command as a String
    // if (gesture == "Gesture1") {
    //     return "Turn on the lights";
    // } else if (gesture == "Gesture2") {
    //     return "Play music";
    // } else if (gesture == "Gesture3") {
    //     return "Stop";
    // }
    // Add more mappings as needed
    return "Unknown gesture";
}

void convertTextToSpeech(String textCommand) {
    // Call Google TTS library or other TTS service to convert text to speech
    // Play the generated speech using the Audio library
    audio.connecttospeech(textCommand.c_str(), "en");
    audio.loop();
}

