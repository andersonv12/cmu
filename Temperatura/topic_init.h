#include "gpio_init.h"
#define TOPICODALLAS "/rna/sensorDallas"
#define TOPICODHTT "/rna/sensorDHT/Temperature"
#define TOPICODHTH "/rna/sensorDHT/Humidity"

int staTop1 = LOW;
int staTop2 = LOW;

// 
//FunÃ§Ã£o: Trata o valor do Topico
//ParÃ¢metros: nenhum
//Retorno: nenhum
void trataTopico(char* topic,String msg){
    Serial.print(topic);
    Serial.print(" ");
      
    if (strcmp(topic,TOPICODALLAS)==0){
      Serial.println(msg.toFloat());
    
      if(msg.toFloat() > 25.0){
        stagrn = HIGH;
      } else {
        stagrn = LOW;
      }
    }

    if (strcmp(topic,TOPICODHTT)==0){
      Serial.println(msg.toFloat());
      if(msg.toFloat() > 25.0){
        stared = HIGH;
      } else {
        stared = LOW;
      }
    }

    digitalWrite(GRNLED, stagrn);
    digitalWrite(REDLED, stared);
  
}
