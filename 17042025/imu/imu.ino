#include "Arduino_BHY2.h"

SensorXYZ accelerometer(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

void setup(){
  Serial.begin(115200);
  BHY2.begin();

  accelerometer.begin();
  gyro.begin();
}

void loop(){
  static auto lastCheck = millis();

  // Update function should be continuously polled
  BHY2.update();

  // Check sensor values every second  
  if (millis() - lastCheck >= 1000) {
    lastCheck = millis();

    Serial.println(String("acceleration: ") + accelerometer.toString());
    Serial.println(String("gyroscope: ") + gyro.toString());
  }
}

short accX = accelerometer.x();
short accY = accelerometer.y();
short accZ = accelerometer.z();

short gyroX = gyroscope.x();
short gyroY = gyroscope.y();
short gyroZ = gyroscope.z();