#include <GlobalFunctions.h>
#include <Constants.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>


/* Set these to your desired credentials. */
const char *ssid = "ESP-ap";
const char *password = "test123";

ESP8266WebServer server(80);
int activeFlag;
String message;
int handleTime;

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
  server.send(200, "application/json", MSG_STATUS_OK);
}

bool sendJsonResponseToClient(String msg = message){    
  //Send data from arduino to Client
  String toSend = GlobalFunctions::getJsonMessage(msg);
  if(toSend == ""){
    //invalid json message
    server.send(200, "application/json", MSG_NO_RESPONSE_FROM_ARDUINO);
    return false;
  }
  server.send(200, "application/json", toSend);
  
  //resetting message after sending it to the Client
  message = "";
  return true;
}

bool sendToArduino(){
  if(server.hasArg("plain") != true){
      server.send(200, "application/json", MSG_NO_BODY_IN_REQUEST);
      return false;
  }
  Serial.print(server.arg("plain"));

  server.send(200, "application/json", MSG_STATUS_OK);
  return true;
}

void handleStartBikesession(){
  if(activeFlag == SESSION_NOT_ACTIVE){  
    if(sendToArduino()){
     activeFlag = SESSION_ACTIVE; 
    }
  }else{
    server.send(200, "application/json", MSG_SESSION_ALREADY_ACTIVE);
  }
}

void handleGetData(){
  if(activeFlag == SESSION_ACTIVE){
    sendJsonResponseToClient();
  }else{
    server.send(200, "application/json", MSG_SESSION_NOT_ACTIVE);
  }
}

void handleStop(){
  if(activeFlag == SESSION_ACTIVE){
    if(sendToArduino()){
      activeFlag = SESSION_NOT_ACTIVE;
    }    
  }else{
    server.send(200,"application/json", MSG_SESSION_NOT_ACTIVE);
  }  
}

void setup() {
  delay(1000);
  activeFlag = SESSION_NOT_ACTIVE;
  message = "";
  handleTime = 200;
  Serial.begin(BAUD_RATE);
  
  /* You can remove the password parameter if you want the AP to be open. */
  IPAddress myIP = WiFi.softAP(ssid, password);
  
  server.on("/", handleRoot);
  server.on("/stop", handleStop);  
  server.on("/startBikeSession", handleStartBikesession);
  server.on("/getData",  handleGetData);
  server.begin();
  //Serial.println("HTTP server started");
}

void loop() {
  unsigned long timer = millis();
  while(millis() - timer <= handleTime){
    server.handleClient();
  }
  if(activeFlag == SESSION_ACTIVE){
    //If there is Json message in the buffer which is not getting 
    //handeled, the buffer string is getting resetted
    if(GlobalFunctions::getJsonMessage(message) != ""){
      message = "";
    }    
    //Fuction is used to read the newest data message from the arduino
    //This function is reading for max 100ms
    GlobalFunctions::readJsonFromSerial(&message);
  }
}

