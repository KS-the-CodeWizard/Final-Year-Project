#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 Gyro;
float angle_tilt;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  while(!Serial)
  delay(20);

  if(!Gyro.begin()){
    while(1){
      Serial.println("Gyro.NOT.Ready!!");
      delay(20);
    }
  }
  Serial.println("Gyro..Ready");
}

void loop() {
  // put your main code here, to run repeatedly:

  sensors_event_t acc, gcc, temp;
  Gyro.getEvent(&acc,&gcc,&temp);
  // Serial.println((gcc.gyro.x));
  angle_tilt = gcc.gyro.x; 


    if ((angle_tilt < -1.75) && (angle_tilt > -4.36))
  {
    Serial.println("Gesture 1");
  }
  else if((angle_tilt < 1.75) && (angle_tilt > -1.75))
  {
    Serial.println("Gesture 2");
  }
  else if((angle_tilt < 4.36) && (angle_tilt > 1.75))
  {
    Serial.println("Gesture 3");
  }else
  {
    Serial.println("No Gesture...!!");
  }

  delay(1000);
}
