#include "random_forest_model.h"  // Random Forest Model
#include "Arduino_BHY2.h"

Sensor temp(SENSOR_ID_TEMP);

// Instantiate the object of the RandomForest class
Eloquent::ML::Port::RandomForest model;

float temperature; 

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Test of the model.");

  BHY2.begin();
  temp.begin();
}

void loop() {
  BHY2.update();

  temperature = temp.value();

  float input[1] = {temperature};

  // Esegui la predizione
  int prediction = model.predict(input);

  // Interpreta il risultato
  if (prediction == 0) {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C - Stato: OK");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println("°C - Stato: OUT_OF_RANGE");
  }

  delay(2000);  // Aspetta 2 secondi prima di eseguire di nuovo
}