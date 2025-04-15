#include "ArduinoBLE.h"
#include "Arduino_BHY2Host.h"

Sensor temperature(SENSOR_ID_TEMP);

// Definisci UUID per il servizio e la caratteristica BLE
BLEService temperatureService("1809"); // Servizio per la temperatura
BLEFloatCharacteristic temperatureChar("2A1C", BLERead | BLENotify); // Caratteristica per la temperatura

void setup() {
  Serial.begin(115200); // Inizializza la comunicazione seriale
  while (!Serial);

  // Inizializza il sensore di temperatura
  BHY2Host.begin(false, NICLA_VIA_BLE);
  temperature.begin();

  // Inizializza BLE
  if (!BLE.begin()) {
    Serial.println("Errore nell'inizializzazione di BLE!");
    while (1);
  }

  BLE.setLocalName("NiclaSenseMeTemp");
  BLE.setAdvertisedService(temperatureService);
  temperatureService.addCharacteristic(temperatureChar);
  BLE.addService(temperatureService);
  BLE.advertise();

  Serial.println("Nicla Sense Me attiva, in attesa di connessioni...");
}

void loop() {
  BLEDevice central = BLE.central(); // Attende una connessione dal dispositivo centrale

  if (central) {
    Serial.print("Connesso al dispositivo centrale: ");
    Serial.println(central.address());

    while (central.connected()) {
      float temp = temperature.value(); // Leggi il valore della temperatura
      temperatureChar.writeValue(temp); // Invia il valore tramite BLE
      Serial.print("Temperatura inviata: ");
      Serial.println(temp);
      delay(1000); // Invia ogni secondo
    }

    Serial.print("Disconnesso da: ");
    Serial.println(central.address());
  }
}
