#include "Arduino.h"
#include "Arduino_BHY2.h"
#include <Wire.h>

// Initialize sensors
Sensor temperature(SENSOR_ID_TEMP);
Sensor humidity(SENSOR_ID_HUM);
SensorBSEC bsec(SENSOR_ID_BSEC);

// Variables to store sensor values
float tempValue;
float humValue;
uint16_t iaqValue;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Begin Eslov with I2C
  BHY2.begin(NICLA_I2C, NICLA_VIA_ESLOV);

  // Initialize I2C as a slave with the Eslov address 0x29
  Wire.begin(0x29);
  Wire.onRequest(sendData);

  // Initialize sensors
  temperature.begin();
  humidity.begin();
  bsec.begin();
}

void loop() {
  // Update sensors and store their values
  BHY2.update();
  tempValue = temperature.value();
  humValue = humidity.value();
  iaqValue = bsec.iaq();

  delay(1000); // Update data every second
}

// Function to send data to the master when requested
void sendData() {
  // Send sensor data over I2C as bytes
  Wire.write((uint8_t*)&tempValue, sizeof(tempValue));
  Wire.write((uint8_t*)&humValue, sizeof(humValue));
  Wire.write((uint8_t*)&iaqValue, sizeof(iaqValue));
}