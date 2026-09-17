#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

#include <HardwareSerial.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "M-306_4G"
#define WIFI_PASSWORD "M306@abode"

#define API_KEY "AIzaSyCVbBy_T-Cs78XlRQEbqn60AOPCyuKEn04"
#define DATABASE_URL "https://agrobot-832c9-default-rtdb.asia-southeast1.firebasedatabase.app/" 

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int humidity, moistureValue;
float temperature;

int firstComma, secondComma;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false; 

void setup(){
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial2.begin(9600,SERIAL_8N1, 18, 19);
  Serial1.begin(9600, SERIAL_8N1, 26, 27);
  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Connected to cloud!");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if(Serial.available()){
    Serial.print("Received data from ESP8266(Slave1): ");
    String data1 = Serial.readString();
    if(data1 == "Sensor not working"){
      Serial.println("Sensor not working");
      delay(1000);
    }
    else{
      moistureValue = data1.toInt();  // will read up to first comma

      firstComma = data1.indexOf(",");
      temperature = data1.substring(firstComma+1).toFloat();  //will read up to second comma
  
      secondComma = data1.indexOf(",",firstComma+1);
      humidity = data1.substring(secondComma+1).toInt();   //will read to end of string

      Serial.println(moistureValue);
      Serial.println(temperature,1);
      Serial.println(humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave1/DHT_11/Temperature/Data", temperature);
      Firebase.RTDB.setInt(&fbdo, "Slave1/DHT_11/Humidity/Data", humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave1/DHT_11/Soil Moisture/Data", moistureValue);      
      delay(1000);
    }
  }
    if(Serial1.available()){
    Serial.print("Received data from ESP8266(Slave2): ");
    String data2 = Serial1.readString();
    if(data2 == "Sensor not working"){
      Serial.println("Sensor not working");
      delay(1000);
    }
    else{
      moistureValue = data2.toInt();  // will read up to first comma

      firstComma = data2.indexOf(",");
      temperature = data2.substring(firstComma+1).toFloat();  //will read up to second comma
  
      secondComma = data2.indexOf(",",firstComma+1);
      humidity = data2.substring(secondComma+1).toInt();   //will read to end of string

      Serial.println(moistureValue);
      Serial.println(temperature,1);
      Serial.println(humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave2/DHT_11/Temperature/Data", temperature);
      Firebase.RTDB.setInt(&fbdo, "Slave2/DHT_11/Humidity/Data", humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave2/DHT_11/Soil Moisture/Data", moistureValue);      
      delay(1000);
    }
  }
     if(Serial2.available()){
    Serial.print("Received data from ESP8266(Slave3): ");
    String data3 = Serial2.readString();
    if(data3 == "Sensor not working"){
      Serial.println("Sensor not working");
      delay(1000);
    }
    else{
      moistureValue = data3.toInt();  // will read up to first comma

      firstComma = data3.indexOf(",");
      temperature = data3.substring(firstComma+1).toFloat();  //will read up to second comma
  
      secondComma = data3.indexOf(",",firstComma+1);
      humidity = data3.substring(secondComma+1).toInt();   //will read to end of string

      Serial.println(moistureValue);
      Serial.println(temperature,1);
      Serial.println(humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave3/DHT_11/Temperature/Data", temperature);
      Firebase.RTDB.setInt(&fbdo, "Slave3/DHT_11/Humidity/Data", humidity);
      Firebase.RTDB.setInt(&fbdo, "Slave3/DHT_11/Soil Moisture/Data", moistureValue);
      delay(1000);
    }
  }
}
