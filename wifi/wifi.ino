#include <ESP8266WiFi.h>

//definizione parametri statici rete wifi
const char* nome_rete = "progetto_embedded";
const char* pw_rete   = "arduino2019";

void setup() {
  WiFi.begin(nome_rete,pw_rete);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

void loop() { }
