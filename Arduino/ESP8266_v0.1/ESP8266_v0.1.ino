/* Create a WiFi access point and provide a web server on it. */
#include <Constants.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


/* Set these to your desired credentials. */
const char *ssid = "ESP-ap";
const char *password = "test123";

ESP8266WebServer server(80);
int activeFlag = 0;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "text/html", "<h1>You are connected</h1>");
}

void sendJson(){  
  String recievedStr = Serial.readString();
  if(recievedStr != ""){    
    server.send(200, "application/json", recievedStr);
  }  
}

void handelStart(){
  activeFlag = SESSION_ACTIVE;
}

void handleStop(){
  activeFlag = SESSION_NOT_ACTIVE;
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	
	/* You can remove the password parameter if you want the AP to be open. */
	IPAddress myIP = WiFi.softAP(ssid, password);
  
  Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
  server.on("/stop", handleStop);  
  server.on("/start", handleStop);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
  if(activeFlag == SESSION_ACTIVE && Serial.readString().equals(ARDUINO_STARTS_SENDING)){
    sendJson();
  }
}
