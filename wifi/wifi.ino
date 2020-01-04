#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//definizione parametri statici rete wifi
const char* nome_rete = "progetto_embedded";
const char* pw_rete   = "arduino2019";

#define mqtt_port 10954
#define mqtt_user "user"
#define mqtt_pwd  "password"
#define mqtt_address "farmer.cloudmqtt.com"

WiFiClient guest;
PubSubClient client(guest);

//avvia una connessione al server mqtt 
void mqtt_connect(){
  client.setServer(mqtt_address,mqtt_port);

  while(!client.connected()) {
    if(client.connect("esp8266",mqtt_user,mqtt_pwd)) {
      break;
    } 
    else {
      delay(2000);
    }
  }
}

//permette l'invio di messaggi tramite mqtt
void mqtt_send(){
  char message[100];
  const char* startmessage = "Area violata";
  
  strcpy(message,startmessage);
  client.publish("alarm", message);
}


void setup() {
  //connessione a rete wifi pre-impostata
  WiFi.begin(nome_rete,pw_rete);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  //connessione a server mqtt
  mqtt_connect();
}

void loop() { 
  client.loop();
  mqtt_send();
  delay(3000);
}
