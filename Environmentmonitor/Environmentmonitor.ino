/*
Code Name:Internet of things based environment monitor
Author: @ammarece
Description: This program is Internet of things based environment monitor
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/
#define BLYNK_TEMPLATE_ID "TMPL3pODcIp8O"
#define BLYNK_TEMPLATE_NAME "Environment monitor"
#define BLYNK_AUTH_TOKEN "Kpg39ztV0ah1aSYKkAGMn7aswuLTCAvL"
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "iMaK";
char pass[] = "gate@024";

// Blynk authentication token
char auth[] = "Kpg39ztV0ah1aSYKkAGMn7aswuLTCAvL";

// Define DHT type and pin
#define DHTPIN 2   // GPIO2 on most ESP8266 boards
#define DHTTYPE DHT11

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Define MQ gas sensor analog pin
#define MQ_PIN A0

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  Blynk.run();

  // Read temperature and humidity from DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read air quality from MQ gas sensor
  int airQuality = analogRead(MQ_PIN);

  // Send temperature, humidity, and air quality data to Blynk
  Blynk.virtualWrite(V0, temperature); // Virtual Pin for temperature
  Blynk.virtualWrite(V1, humidity);    // Virtual Pin for humidity
  Blynk.virtualWrite(V2, airQuality);  // Virtual Pin for air quality

  // Print data to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Air Quality: ");
  Serial.println(airQuality);

  delay(1000); // Read and send data every second
}
