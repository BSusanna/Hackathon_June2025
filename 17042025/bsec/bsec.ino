#include "Arduino_BHY2.h"

SensorBSEC bsec(SENSOR_ID_BSEC);

void setup(){
  Serial.begin(115200);
  while (!Serial); // Wait for Serial to initialize

  if (!BHY2.begin()) {
    Serial.println("Failed to initialize BHY2 sensor hub!");
    while (1); // Halt if initialization fails
  }

  if (!bsec.begin()) {
    Serial.println("Failed to initialize BSEC sensor!");
    while (1); // Halt if BSEC initialization fails
  }
}

void loop(){
  static unsigned long lastCheck = millis();
  BHY2.update();

  if (millis() - lastCheck >= 1000) {
    lastCheck = millis(); // Update the last check time

    // Read individual BSEC values
    uint16_t iaqValue = bsec.iaq();
    float vocEquivalent = bsec.b_voc_eq();
    uint32_t co2Equivalent = bsec.co2_eq();

    // Print the values to the serial monitor
    Serial.print("IAQ Value: ");
    Serial.println(iaqValue);
    Serial.print("VOC Equivalent (ppm): ");
    Serial.println(vocEquivalent);
    Serial.print("CO2 Equivalent (ppm): ");
    Serial.println(co2Equivalent);
  }
}