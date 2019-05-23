#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "config.h"
#include "wifi_init.h"
#include "mqtt_init.h"
 
OneWire pino(D3);
DallasTemperature barramento(&pino);
DeviceAddress sensor_1;
DHT dht(D5, DHT11);
 
void setup(void)
{
  Serial.begin(115200);
  barramento.begin();
  barramento.getAddress(sensor_1, 0);

  dht.begin();

  Serial.print("Neste barramento foram encontrados ");
  Serial.print(barramento.getDeviceCount(), DEC);
  Serial.println(" sensores.");

  barramento.getAddress(sensor_1, 0);

  iniciaGPIO();
  if (conectaWiFi()){
     iniciaMQTT();
  }   
  
}
 
void loop()
{
  barramento.requestTemperatures(); 
  float temperatura_sensor_1 = barramento.getTempC(sensor_1);
//  Serial.print("Sensor Dallas: ");
//  Serial.print(temperatura_sensor_1);
//  Serial.println("ºC");
//  Serial.print("Sensor DHT: ");
//  Serial.print(dht.readTemperature());
//  Serial.print(" ºC / ");
//  Serial.print(dht.readHumidity());
//  Serial.println("%");
//  delay(1000);


  if (WiFi.status() == WL_CONNECTED){
      if (!MQTTClient.connected()) {
        connectaClienteMQTT();
      }
      MQTTClient.publish(TOPICODALLAS, String(temperatura_sensor_1).c_str());
      MQTTClient.publish(TOPICODHTT, String(dht.readTemperature()).c_str());
      MQTTClient.publish(TOPICODHTH, String(dht.readHumidity()).c_str());
      MQTTClient.loop(); 
  }else{
     if (conectaWiFi()){
     iniciaMQTT();
     }   
      
  }

  
}
