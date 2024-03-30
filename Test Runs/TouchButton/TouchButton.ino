

#include "Arduino.h"

int threshold = 40;
bool touchActive = false;
bool lastTouchActive = false;
bool testingLower = true;

void gotTouchEvent(){
  if (lastTouchActive != testingLower) {
    touchActive = !touchActive;
    testingLower = !testingLower;
    touchInterruptSetThresholdDirection(testingLower);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 Touch Interrupt Test");
  pinMode(LED_BUILTIN, OUTPUT);
  touchAttachInterrupt(T6, gotTouchEvent, threshold);

  touchInterruptSetThresholdDirection(testingLower);
}

void loop(){
  if(lastTouchActive != touchActive){
    lastTouchActive = touchActive;
    if (touchActive) {
      Serial.println("  ---- Touch was Pressed");
      digitalWrite(LED_BUILTIN, HIGH);  
      delay(100); 
    } else {
      Serial.println("  ---- Touch was Released");
      digitalWrite(LED_BUILTIN, LOW); 
      delay(100); 
    }
  }
  Serial.printf("T2 pin2 = %d \n", touchRead(T6));
  delay(300);
}

