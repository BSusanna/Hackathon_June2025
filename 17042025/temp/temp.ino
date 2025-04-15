#include "Arduino_BHY2.h"

Sensor temperature(SENSOR_ID_TEMP);

void setup(){
  Serial.begin(115200);
  BHY2.begin();
  temperature.begin();
}

void loop(){
  static auto lastCheck= millis();
  BHY2.update();

  // Check sensor values every second  
  if (millis() - lastCheck >= 1000) {
    lastCheck = millis();
    Serial.println(String("temperature: ") + String(int(temperature.value())));
  }
}