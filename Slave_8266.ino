#include <ESP8266WiFi.h>
#include <DHT.h>

#define BAUD_RATE 9600
#define DHT_PIN 4 
#define DHTTYPE DHT11
int moisturePin = 16;

DHT dht(DHT_PIN, DHTTYPE);

void setup() {
  Serial.begin(BAUD_RATE);
  delay(100);
  dht.begin();
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int moistureValue = analogRead(moisturePin);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(10000);
    return;
  }
  // Send data via UART (Serial)
  Serial.print(moistureValue);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(temperature);
  Serial.print(",");
  delay(20000);
}
