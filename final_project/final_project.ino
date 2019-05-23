#include <DHT.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "MQTT.h"

#define LIGHT A0
#define TEMP_HUMI D5
#define SOIL D6
#define RELAY D7

#define NET_SSID        "saeg2019"
#define NET_PASS        "semsenha"
#define MQTT_SERV       "iotsaeg.nc2.iff.edu.br"
#define MQTT_USER       "saeg"
#define MQTT_PASS       "semsenha"
#define MQTT_PORT       1883
#define TOPIC           "/anderson/final"


DHT dht(TEMP_HUMI, DHT11);
char output[300];

char* getJson(float dht_temperature, float dht_humidity, int luminosity, bool soil_humidity){
  StaticJsonDocument<300> doc;
  
  JsonObject sensor;
  sensor = doc.createNestedObject();
  sensor["name"] = "DHT";
  sensor["type"] = "temperature";
  sensor["value"] = dht_temperature;
  
  sensor = doc.createNestedObject();
  sensor["name"] = "DHT";
  sensor["type"] = "humidity";
  sensor["value"] = dht_humidity;
  
  sensor = doc.createNestedObject();
  sensor["name"] = "LDR";
  sensor["type"] = "luminosity";
  sensor["value"] = luminosity;
  
  sensor = doc.createNestedObject();
  sensor["name"] = "HL69";
  sensor["type"] = "humidity";
  sensor["value"] = !soil_humidity;
  
  serializeJson(doc, output);
  return output;
}

void setup() {
  Serial.begin(9600);
  pinMode(SOIL, INPUT);
  pinMode(RELAY, OUTPUT);
  dht.begin();
}

void MQTTCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
     message += (char)payload[i];
  }
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);
  delay(2000); 
}

void loop() {
  if (!wifiConnected()) {
    connectWifi(NET_SSID, NET_PASS);
  }
  if (!MQTTLoop()) {
    connectMQTT(MQTT_SERV, MQTT_PORT, MQTT_USER, MQTT_PASS);
    subscribeTopic(TOPIC);
  } else {
    publishTopic(TOPIC, getJson(dht.readTemperature(), dht.readHumidity(), analogRead(LIGHT), digitalRead(SOIL)));
  }
}
