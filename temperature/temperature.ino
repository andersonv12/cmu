#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "WiFi.h"
#include "MQTT.h"

#define NET_SSID        "saeg2019"
#define NET_PASS        "semsenha"
#define MQTT_SERV       "iotsaeg.nc2.iff.edu.br"
#define MQTT_USER       "saeg"
#define MQTT_PASS       "semsenha"
#define MQTT_PORT       1883
#define TOPIC_DALLAS    "/saeg/dallas/temperature"
#define TOPIC_DHT_TEMP  "/saeg/dht/temperature"
#define TOPIC_DHT_HUMI  "/saeg/dht/humidity"
#define GREEN_LED       D2
#define RED_LED         D4

OneWire pin(D3);
DallasTemperature bus(&pin);
DeviceAddress dallas;
DHT dht(D5, DHT11);

void setup() {
  Serial.begin(9600);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  
 // bus.begin();
  //bus.getAddress(dallas, 0);

  dht.begin();
}

void loop() {
  if (!wifiConnected()) {
    if (connectWifi(NET_SSID, NET_PASS)) {
      connectMQTT(MQTT_SERV, MQTT_PORT, MQTT_USER, MQTT_PASS);
      subscribeTopic(TOPIC_DHT_TEMP);
    }
  } else if (!MQTTLoop()) {
    connectMQTT(MQTT_SERV, MQTT_PORT, MQTT_USER, MQTT_PASS);
    subscribeTopic(TOPIC_DHT_TEMP);
  } else {
    bus.requestTemperatures(); 
    publishTopic(TOPIC_DALLAS, (char*) String(bus.getTempC(dallas)).c_str());
    publishTopic(TOPIC_DHT_TEMP, (char*) String(dht.readTemperature()).c_str());
    publishTopic(TOPIC_DHT_HUMI, (char*) String(dht.readHumidity()).c_str());  
  }
}

void MQTTCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
     message += (char)payload[i];
  }    
  if (strcmp(topic, TOPIC_DALLAS) == 0) {
    if (message.toFloat() > 25) {
      digitalWrite(GREEN_LED, HIGH);
    } else {
     digitalWrite(GREEN_LED, LOW);
    }      
  }
  if (strcmp(topic, TOPIC_DHT_TEMP) == 0) {
    if (message.toFloat() > 25) {
      digitalWrite(RED_LED, HIGH);
    } else {
     digitalWrite(RED_LED, LOW);
    }      
  }
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message.toFloat());
  delay(1000); 
}
