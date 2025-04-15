#include "Arduino_BHY2.h"

Sensor gas(SENSOR_ID_GAS);

void setup() {
  Serial.begin(115200);
  BHY2.begin();
  gas.begin();
}

void loop(){
  static auto lastCheck= millis();
  BHY2.update();

  // Check sensor values every second  
  if (millis() - lastCheck >= 1000) {
    lastCheck = millis();
    Serial.println(String("gas: ") + String(gas.value()));
  }
}