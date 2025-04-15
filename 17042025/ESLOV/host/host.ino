#include <Arduino.h>
#include <Wire.h>

float tempValue;
float humValue;
uint16_t iaqValue;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize I2C as the master
  Wire.begin();
}

void loop() {
  // Request data from Nicla Sense ME
  Wire.requestFrom(0x29, sizeof(tempValue) + sizeof(humValue) + sizeof(iaqValue));

  // Read data if available
  if (Wire.available() >= sizeof(tempValue) + sizeof(humValue) + sizeof(iaqValue)) {
    Wire.readBytes((char*)&tempValue, sizeof(tempValue));
    Wire.readBytes((char*)&humValue, sizeof(humValue));
    Wire.readBytes((char*)&iaqValue, sizeof(iaqValue));

    // Print data to serial monitor
    Serial.print("Temperature: ");
    Serial.println(tempValue);
    Serial.print("Humidity: ");
    Serial.println(humValue);
    Serial.print("IAQ: ");
    Serial.println(iaqValue);
  }

  delay(1000); // Process data every second
}