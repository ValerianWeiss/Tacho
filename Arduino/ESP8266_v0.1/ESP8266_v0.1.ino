
#include <Constants.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


/* Set these to your desired credentials. */
const char *ssid = "ESP-ap";
const char *password = "test123";

ESP8266WebServer server(80);
int activeFlag = SESSION_NOT_ACTIVE;


/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void sendJsonResponseToClient(){  
  String recievedStr = "";
  //Reading data from arduino
  while(Serial.available() > 0 && !recievedStr.endsWith("\n") || recievedStr ==  ""){
    recievedStr += Serial.readString();
  }
  //Send data from arduino to Client
  server.send(200, "application/json", recievedStr);  
}

void handleStartBikesession(){
  if(activeFlag != SESSION_ACTIVE){  
    sendToArduino();
    activeFlag = SESSION_ACTIVE;
  }else{
    server.send(404, "application/json", "{\"status\":\"-3\"}");
  }
}

void sendToArduino(){
  if(server.hasArg("plain") != true){
      server.send(404, "application/json", "{\"status\":\"-1\"}");
      return;
    }
    Serial.print(server.arg("plain"));
    Serial.print("\n");
    //the response which is getting produced and send by to arduino
    sendJsonResponseToClient();
}

void handleStop(){
  if(activeFlag != SESSION_NOT_ACTIVE){
    sendToArduino();
    activeFlag = SESSION_NOT_ACTIVE;      
  }else{
    server.send(404,"application/json", "{\"status\":\"-3\"}");
  }  
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  //Serial.println();
  //Serial.print("Configuring access point...");
  
  /* You can remove the password parameter if you want the AP to be open. */
  IPAddress myIP = WiFi.softAP(ssid, password);
  
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/stop", handleStop);  
  server.on("/startBikeSession", handleStartBikesession);
  server.begin();
  //Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  if(activeFlag == SESSION_ACTIVE){
    sendJsonResponseToClient();
  }
}

