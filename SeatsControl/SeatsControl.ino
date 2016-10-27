#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
MDNSResponder mdns;
 
const int PINO_TRIGGER_SENSOR_1 = 4;
const int PINO_ECHO_SENSOR_1 = 5;
const int PINO_TRIGGER_SENSOR_2 = 13;
const int PINO_ECHO_SENSOR_2 = 15;
 
const char *SENSOR_ID_1 = "1";
const char *SENSOR_ID_2 = "2";
const char *HOST_NAME = "us1";
const char* ssid = "LAB-DIGITAL";
const char* password = "LABDIGITAL@123";
 
ESP8266WebServer server(8081);
 
void setup(void){
//  Serial.begin(115200);
// Alterado para 9600 de acordo com as especificações na propria placa  
  Serial.begin(9600);
  
  // preparing GPIOs
  pinMode(PINO_TRIGGER_SENSOR_1, OUTPUT);
  pinMode(PINO_ECHO_SENSOR_1, INPUT);
 
  pinMode(PINO_TRIGGER_SENSOR_2, OUTPUT);
  pinMode(PINO_ECHO_SENSOR_2, INPUT);
 
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  
  if (n == 0){
    Serial.println("no networks found");
    Serial.println("Going into sleep");
    // ESP.deepSleep(sleepTimeS * 1000000);
  }
  
  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin(HOST_NAME, WiFi.localIP())) {
    Serial.println("MDNS responder started with name: " + String(HOST_NAME));
  }
 
//  server.on("/", [](){
//    long tempoEco, distancia1, distancia2;
 
    //--- gera um pulso no pino trigger do sensor    
//    digitalWrite(PINO_TRIGGER_SENSOR_1, LOW);
//    delayMicroseconds(2);
//    digitalWrite(PINO_TRIGGER_SENSOR_1, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(PINO_TRIGGER_SENSOR_1, LOW);
//    
//    //--- le atraso da resposta no pino echo
//    tempoEco = pulseIn(PINO_ECHO_SENSOR_1, HIGH);
////    Serial.println('tempoEco: ' + String(tempoEco));
//    //--- o calculo da distancia considera que a velocidade do som = 343.5 m/s
//    distancia1 = (tempoEco/2) / 29.1;
// 
//    //--- gera um pulso no pino trigger do sensor
//    digitalWrite(PINO_TRIGGER_SENSOR_2, LOW);
//    delayMicroseconds(2);
//    digitalWrite(PINO_TRIGGER_SENSOR_2, HIGH);
//    delayMicroseconds(10);
//    digitalWrite(PINO_TRIGGER_SENSOR_2, LOW);
//    
//    //--- le atraso da resposta no pino echo
//    tempoEco = pulseIn(PINO_ECHO_SENSOR_2, HIGH);
//    //--- o calculo da distancia considera que a velocidade do som = 343.5 m/s
//    Serial.println('tempoEco: ' + String(tempoEco));
//    distancia2 = (tempoEco/2) / 29.1;
//
//    String body = "[";
//    body = body +  "{\"device\": \"" + String(HOST_NAME) + "\", \"sensor\": \"" + String(SENSOR_ID_1) + "\", \"distance\": \"" + String(distancia1) + "\"},";
//    body = body +  "{\"device\": \"" + String(HOST_NAME) + "\", \"sensor\": \"" + String(SENSOR_ID_2) + "\", \"distance\": \"" + String(distancia2) + "\"}";
//    body = body + "]";
//    server.send(200, "application/json", body);
//    
//  });
//  
//  server.begin();
}
 
void loop(void){
    long tempoEco, distancia1, distancia2;
 
    //--- gera um pulso no pino trigger do sensor    
    digitalWrite(PINO_TRIGGER_SENSOR_1, LOW);
    delayMicroseconds(2);
    digitalWrite(PINO_TRIGGER_SENSOR_1, HIGH);
    delayMicroseconds(10);
    digitalWrite(PINO_TRIGGER_SENSOR_1, LOW);
    
    //--- le atraso da resposta no pino echo
    tempoEco = pulseIn(PINO_ECHO_SENSOR_1, HIGH);
//    Serial.println('tempoEco: ' + String(tempoEco));
    //--- o calculo da distancia considera que a velocidade do som = 343.5 m/s
    distancia1 = (tempoEco/2) / 29.1;

  Serial.print("Distancia: ");
  Serial.print(distancia1);
  Serial.println(" cm");

// Retirado o server para facilitar
//  server.handleClient();
} 
