#include <PubSubClient.h>

WiFiClient wifiClient;
PubSubClient MQTTClient(wifiClient);

void MQTTCallback(char* topic, byte* payload, unsigned int length);

void connectMQTT(char* broker, int port, char* user, char* pass) {
  MQTTClient.setServer(broker, port);
  MQTTClient.setCallback(MQTTCallback);
  while (!MQTTClient.connected()) {
    Serial.println("Trying to connect MQTT client to the MQTT Broker...");
    String clientID = "ESP8266-";
    clientID += String(random(0xffff), HEX);
    if (MQTTClient.connect(clientID.c_str(), user, pass)) {
      Serial.println("MQTT client connected successfully!");
      Serial.print("Client ID: ");
      Serial.println(clientID);
    } else {
      Serial.println("MQTT connection error. Trying again...");
      delay(1000);
    }
  }
}

void subscribeTopic(char* topic) {
  MQTTClient.subscribe(topic);  
}

void publishTopic(char* topic, char* payload) {
  MQTTClient.publish(topic, payload); 
}

boolean MQTTLoop() {
  return MQTTClient.loop();
}
