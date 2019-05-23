#include <DHT.h>
#include <ArduinoJson.h>
#include "WiFi.h"
#include "MQTT.h"

#define NET_SSID        "saeg2019"
#define NET_PASS        "semsenha"
#define MQTT_SERV       "iotsaeg.nc2.iff.edu.br"
#define MQTT_USER       "saeg"
#define MQTT_PASS       "semsenha"
#define MQTT_PORT       1883
#define TOPIC           "/saeg/dht_sensor"

DHT dht(D5, DHT11);

float humidity = 0.0;
float temperature = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (!wifiConnected()) {
    if (connectWifi(NET_SSID, NET_PASS)) {
      connectMQTT(MQTT_SERV, MQTT_PORT, MQTT_USER, MQTT_PASS);
      subscribeTopic(TOPIC);
    }
  } else if (!MQTTLoop()) {
    connectMQTT(MQTT_SERV, MQTT_PORT, MQTT_USER, MQTT_PASS);
    subscribeTopic(TOPIC);
  } else {
    publishTopic(TOPIC, createJson(dht.readTemperature(), dht.readHumidity()));
  }
}

char* createJson(float temperatura, float umidade){
  StaticJsonDocument<500> doc;
  doc["sensor"] = "DHT11";
  doc["typeSensor"]="TempHum";
  doc["time"]="1234567890";
  JsonArray values = doc.createNestedArray("data");
  values.add(temperatura);
  values.add(umidade);
  char json[256];
  serializeJson(doc, json);;
  return json;
}

void MQTTCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
     message += (char)payload[i];
  }
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);
  delay(1000); 
}
