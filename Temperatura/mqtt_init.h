#include <PubSubClient.h> //Importa biblioteca MQTT
#include "topic_init.h"

//constantes e variÃ¡veis globais
PubSubClient MQTTClient(wifiClient);


//prototypes

void connectaClienteMQTT(void);
void iniciaMQTT(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
String mensagem(byte* payload, unsigned int length);
void trataTopico(char* topic, String msg);

void connectaClienteMQTT(void) {
  // Espera atÃ© estar conectado ao servidor
  while (!MQTTClient.connected()) {
    Serial.println("Tentando MQTT connection...");
    
    // Tentativa de conexÃ£o
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if( MQTTClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS )) {
      Serial.println("connected: "+clientId);
      MQTTClient.subscribe(TOPICODALLAS);
      MQTTClient.subscribe(TOPICODHTT);
    } else {
      Serial.print("failed, rc=");
      Serial.print(MQTTClient.state());
      Serial.println(" try again in 5 seconds");
      // Espera 2 segundo e tenta novamente
      delay(5000);
    }
  }
}

void iniciaMQTT(void){
  MQTTClient.setServer(MQTT_SERVER, PORTA);
  MQTTClient.setCallback(mqtt_callback); 
}

String mensagem(byte* payload, unsigned int length){

  String msg;
 
  //obtem a string do payload recebido
  for(int i = 0; i < length; i++) 
  {
     char c = (char)payload[i];
     msg += c;
  }
  return msg;
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{     
    String msg = mensagem(payload,length);
    
    trataTopico(topic,msg);
    
}
