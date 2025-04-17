#include <Arduino.h>
#include <WiFiNINA.h>
#include <WiFiSSLClient.h>
#include "Arduino_BHY2Host.h"

#include "arduino_secrets.h" // Include your WiFi credentials 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int currentButtonState;
int lastButtonState = 0;
boolean buttonSwitch = false;

char server[] = "script.google.com";

String url = "";

WiFiSSLClient client;

Sensor temp(SENSOR_ID_TEMP);
Sensor hum(SENSOR_ID_HUM);

// Declaring the arrays where temperature and humidity data will be saved every minute, so 60 times an hour
float temperatures[60];
float humidities[60];

unsigned int dataIndex = 0;
unsigned long lastDataSentTime = 0;
unsigned long lastDataSavedTime = 0;
unsigned long dataSendInterval = 300000; // 5 minutes interval for data send (300,000ms)

void setup() 
{
  Serial.begin(9600);
  while (!Serial);

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to network:");
    Serial.println(ssid);
    delay(5000);
  }

  Serial.println("Connected to WiFi");
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Initializing Nicla Sense ME...");
  BHY2Host.begin(false, NICLA_VIA_ESLOV);
  temp.begin();
  hum.begin();

  Serial.println("Setup complete");
}

void loop() 
{
  currentButtonState = digitalRead(BUTTON_PIN);
  if (currentButtonState) // If the button is pressed
  {
    if (!lastButtonState) // If it was not pressed previously
    {
      buttonSwitch = !buttonSwitch;
      if(buttonSwitch) 
      {
        Serial.println("ON");
        digitalWrite(LED_BUILTIN, HIGH);     
      }
      else 
      { 
        if (sendDataToGoogleSheets()) 
        {
          Serial.println("Data sent to Google Sheets successfully");
        } 
        else 
        {
          Serial.println("Failed to send data to Google Sheets");
        }
        Serial.println("OFF");
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }
  BHY2Host.update();
  lastButtonState = currentButtonState;
  
  if(buttonSwitch)
  { 
    if (millis() - lastDataSavedTime >= 60000) // Every minute
    { 
      lastDataSavedTime = millis();

      // Gather temperature and humidity data every minute
      temperatures[dataIndex] = temp.value();
      humidities[dataIndex] = hum.value();

      Serial.print(dataIndex + 1);
      Serial.print(") ");
      Serial.print(temperatures[dataIndex]);
      Serial.print("  ");
      Serial.println(humidities[dataIndex]);

      dataIndex++;

      if (dataIndex >= 5) 
      {
        dataIndex = 0; // Reset index to start over after collecting 60 data points (1 hour)
      }

      // Send data to Google Sheets every 5 minutes (after 5 sets of data)
      if (millis() - lastDataSentTime >= dataSendInterval) 
      {
        lastDataSentTime = millis();

        if (sendDataToGoogleSheets()) 
        {
          Serial.println("Data sent to Google Sheets successfully");
        } 
        else 
        {
          Serial.println("Failed to send data to Google Sheets");
        }
      }
    }
  }
}

bool sendDataToGoogleSheets() {
  if (!client.connect(server, 443)) {
    Serial.println("Failed to connect to Google Sheets server");
    return false;
  }

  String data;
  // Send all collected data (temperatures and humidities arrays) as URL parameters
  for (int i = 0; i < 5; i++) {
    data += "&t" + String(i + 1) + "=" + String(temperatures[i]) +
            "&h" + String(i + 1) + "=" + String(humidities[i]);
  }

  Serial.println(data);
  String request = "GET " + url + "?" + data + " HTTP/1.1";
  client.println(request);
  client.println("Host: " + String(server));
  client.println("Connection: close");
  client.println();

  delay(500); // Wait for server response

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }

  if (!client.connected()) {
    Serial.println("Connection to Google Sheets server closed");
  }

  client.stop();
  return true;
}
