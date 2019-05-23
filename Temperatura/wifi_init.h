#include <ESP8266WiFi.h>  //essa biblioteca jÃ¡ vem com a IDE. Portanto, nÃ£o Ã© preciso baixar nenhuma biblioteca adicional

//constantes e variÃ¡veis globais
WiFiClient wifiClient;

//prototypes
boolean conectaWiFi(void);


//FunÃ§Ã£o: faz a conexÃ£o WiFI
//ParÃ¢metros: nenhum
//Retorno: nenhum
boolean conectaWiFi(void)
{
    
    wifiClient.stop();
    
    delay(500);
    Serial.println("Conectando-se Ã  rede WiFi...");
    Serial.println();  
    
    WiFi.begin(SSID_REDE, SENHA_REDE);
    
    int contDelay = 0;
    while ((WiFi.status() != WL_CONNECTED) && (contDelay < 60) ) 
    {
        delay(1000);
        Serial.print(".");
        contDelay++;
        
    }

    if(WiFi.status() != WL_CONNECTED){
       Serial.println("");
       Serial.println("WiFi nÃ£o connectado");
       return false;
    }
      
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());

    
    return true;
}
