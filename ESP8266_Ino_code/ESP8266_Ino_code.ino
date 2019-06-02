#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "CYTA023C";
const char* password = "026813_virus";

MDNSResponder mdns;

ESP8266WebServer server(80);


const int pin_15 = 15;
const int pin_13 = 13;

void handleRoot() {
  server.send(200, "text/plain", 
    "hello from esp8266!) \n/on: to tuen LED ON \n/off: to tuen LED OFF \n");
}

void handleNotFound(){
  //digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
 
void setup(void){
  pinMode(pin_13, OUTPUT);
  pinMode(pin_15, OUTPUT);
  Serial.begin(115200);
  WiFi.begin("CYTA023C", "026813_virus");
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
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);

  server.on("/on_D13", [](){ //D7 Visual
    digitalWrite(pin_13, 1);
    server.send(200, "text/plain", "LED 13 ON");
  });
  
  server.on("/off_D13", [](){ //D7 Visual
    digitalWrite(pin_13, 0);
    server.send(200, "text/plain", "LED 13 OFF");
  });

    server.on("/on_D15", [](){ //D8 Visual
    digitalWrite(pin_15, 1);
    server.send(200, "text/plain", "LED 15 ON");
  });

    server.on("/off_D15", [](){ //D8 visual
    digitalWrite(pin_15, 0);
    server.send(200, "text/plain", "LED 15 OFF");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");

  //delay a moment, 
  //for terminal to receive inf, such as IP address
  delay(1000);
  Serial.end();
}
 
void loop(void){
  server.handleClient();
} 
