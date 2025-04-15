#include <ArduinoBLE.h>

BLECharacteristic temperatureChar("2A1C", BLERead, 4); // La caratteristica della temperatura
BLEDevice peripheral;

void setup() {
  Serial.begin(115200);  // Inizializza la comunicazione seriale
  while (!Serial);

  // Inizializza BLE
  if (!BLE.begin()) {
    Serial.println("Errore nell'inizializzazione di BLE!");
    while (1);
  }

  Serial.println("MKR WiFi 1010 in attesa di connessione...");

  BLE.scanForName("NiclaSenseMeTemp"); // Cerca il dispositivo Nicla Sense Me

  while (!peripheral.connected()) { // Aspetta che la connessione sia stabilita
    peripheral = BLE.available();
    if (peripheral) {
      Serial.println("Dispositivo trovato!");
      peripheral.connect();
    }
  }
}

void loop() {
  if (peripheral.connected()) {
    Serial.println("Connesso alla Nicla Sense Me!");
    
    // Leggi la temperatura
    if (temperatureChar.canRead()) {
      float temp = temperatureChar.read();
      Serial.print("Temperatura ricevuta: ");
      Serial.println(temp);
    }
    delay(1000); // Attende un secondo prima di leggere nuovamente
  }
}

