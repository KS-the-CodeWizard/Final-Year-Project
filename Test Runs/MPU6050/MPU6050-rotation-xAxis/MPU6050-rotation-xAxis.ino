#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

MPU6050 accelgyro;

int16_t ax, ay, az;
float angleX = 0.0; // Angle around the X-axis

#define LED_PIN 2
bool blinkState = false;

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
    #endif

    Serial.begin(38400);
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
    accelgyro.getAcceleration(&ax, &ay, &az);

    // Calculate tilt angle using accelerometer data
    angleX = atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI;

    // Print the tilt angle around X-axis
    Serial.print("Tilt Angle X: ");
    Serial.println(angleX);

}
