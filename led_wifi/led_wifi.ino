#include <ESP8266WiFi.h>

#define NET_SSID "veiga"
#define NET_PASS "andmar89"

WiFiServer server(80);

void setup() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  
  Serial.begin(9600);
  Serial.print("Trying to connect to the wi-fi network: ");
  Serial.println(NET_SSID);

  WiFi.begin(NET_SSID, NET_PASS);

  int attempt = 0;
  while(WiFi.status() != WL_CONNECTED || attempt < 30) {
    delay(200);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nUnable to connect.");
  } else {
    Serial.println("\nSuccessfully connected!");
    server.begin();
    Serial.println("Server started on: http://");
    Serial.print(WiFi.localIP());
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setup();
  } else {
    WiFiClient wifiClient = server.available();
    if (wifiClient.connected()){
      String req = wifiClient.readStringUntil('\r');
      Serial.println(req);
      wifiClient.flush();
      
      if (req.indexOf("/led=on") != -1) {
        digitalWrite(D4, LOW);
      }
      if (req.indexOf("/led=off") != -1) {
        digitalWrite(D4, HIGH);
      }
      
      wifiClient.println("HTTP/1.1 200 OK");
      wifiClient.println("Content-Type:text/html");
      wifiClient.println("");
      wifiClient.println("<!DOCTYPE HTML>");
      wifiClient.println("<html>");
      wifiClient.println("<body>");
      wifiClient.println("<a href='/led=on'>Ligar</a>");
      wifiClient.println("<a href='/led=off'>Desligar</a>");
      wifiClient.println("</body>");
      wifiClient.println("</html>");
    }
  }
}
