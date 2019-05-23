#include <ESP8266WiFi.h>

boolean wifiConnected() {
  return (WiFi.status() == WL_CONNECTED);
}

boolean connectWifi(String ssid, String password) {
  Serial.println("Trying to connect");
  WiFi.begin(ssid, password);

  int countDelay = 0;
  while ((!wifiConnected()) && (countDelay < 10) ) {
    delay(1000);
    Serial.print(".");
    countDelay++;
  }

  if (!wifiConnected()) {
    Serial.println("Wifi connection error. Trying again...");
    delay(1000);
    return false;
  }

  Serial.println("Wifi connected successfully!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}
