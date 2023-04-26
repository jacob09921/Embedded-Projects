 #include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>

ESP8266WebServer server(80);
char* ssid = "Group-2";
char* password = "poginipat";

// hold uploaded file
File fsUploadFile;

// websockets server for handling messages sent by the client
WebSocketsServer webSocket = WebSocketsServer(81);
const byte gear1 = D1;
const byte gear2 = D2;
const byte gear3 = D3;
const byte gear4 = D4;
const byte relay = D5;
int num;


void setup(void)
{
   Serial.begin(115200);
  Serial.print("\n");
  Serial.setDebugOutput(true);
  
  SPIFFS.begin();  

  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);


  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started.");
  
 
  server.onNotFound([](){
    if(!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  server.begin();
  Serial.println("HTTP server started");
  pinMode(gear1, OUTPUT);
  pinMode(gear2, OUTPUT);
  pinMode(gear3, OUTPUT);
  pinMode(gear4, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
}

void loop()
{
  webSocket.loop();
  server.handleClient();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
  if(type == WStype_TEXT)
  {
    // handle the websocket messages with direction and speed
    // by parsing the parameters from a JSON string
    String payload_str = String((char*) payload);
    // using the ArduinoJson library
    StaticJsonDocument<200> doc;
    // deserialize the data
    DeserializationError error = deserializeJson(doc, payload_str);
    // parse the parameters we expect to receive (TO-DO: error handling)
    String dir = doc["direction"];
//    Serial.print("direction: ");
//    Serial.println(dir);
    if(dir == "STP") {
            digitalWrite(gear1, LOW);
            digitalWrite(gear2, LOW);
            digitalWrite(gear3, LOW);
            digitalWrite(gear4, LOW);
      Serial.println("STOP");
      num = 0 + num;
      
    } else {
      int speed = doc["speed"];
      // on the page speed goes from 0 to 100. scale it between 0 and 255:
      speed = map(speed, 0, 100, 0, 255);
      analogWrite(gear1, speed);
      analogWrite(gear3, speed);
      analogWrite(gear2, speed);
      analogWrite(gear4, speed); 
      
      if(dir == "FWD") {
        analogWrite(gear1, speed);
        analogWrite(gear3, speed);
        analogWrite(gear2, LOW);
        analogWrite(gear4, LOW);
        Serial.println("FORWARD");
      } else if(dir == "BWD") {
         analogWrite(gear2, speed);
         analogWrite(gear4, speed);
         analogWrite(gear1, LOW);
         analogWrite(gear3, LOW);;
        Serial.println("BACKWARD");
      } else if(dir == "RGT") {
         analogWrite(gear4, speed);
         analogWrite(gear1, speed);
         analogWrite(gear3, LOW);
         analogWrite(gear2, LOW);
        Serial.println("RIGHT");
      } else if(dir == "LFT") {
       analogWrite(gear3,speed);
       analogWrite(gear2,speed);
       analogWrite(gear1,LOW);
       analogWrite(gear4,LOW);
        Serial.println("LEFT");
      }
      else if(dir == "F-RGT") {
        analogWrite(gear4, LOW);
        analogWrite(gear1, speed);
        analogWrite(gear3, LOW);
        analogWrite(gear2, LOW);
        Serial.println("RIGHT-FORWARD");
      }
      else if(dir == "B-RGT") {
        analogWrite(gear4, LOW);
        analogWrite(gear1, LOW);
        analogWrite(gear3, LOW);
        analogWrite(gear2, speed);
        Serial.println("RIGHT-BACKWARD");
      
    }
    else if(dir == "F-LFT") {
        analogWrite(gear4, LOW);
        analogWrite(gear1, LOW);
        analogWrite(gear3, speed);
        analogWrite(gear2, LOW);
        Serial.println("LEFT-FORWARD");
    }
    else if(dir == "B-LFT") {
         analogWrite(gear4, speed);
         analogWrite(gear1, LOW);
         analogWrite(gear3, LOW);
         analogWrite(gear2, LOW);
        Serial.println("LEFT-BACKWARD");
    }
    else if(dir == "ON") {
       delay(1000);
        digitalWrite(relay, HIGH);
    }
     else if(dir == "OFF") {
        delay(1000);
        
        digitalWrite(relay, LOW);
    }
  
       
    
  
   }
  }
}


void handleFileUpload()
{
  HTTPUpload& upload = server.upload();
  if(upload.status == UPLOAD_FILE_START)
  {
    String filename = upload.filename;
    if(!filename.startsWith("/"))
      filename = "/"+filename;
    Serial.print("handleFileUpload Name: "); Serial.println(filename);
    fsUploadFile = SPIFFS.open(filename, "w");
  } else if(upload.status == UPLOAD_FILE_WRITE)
  {
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize);
  } else if(upload.status == UPLOAD_FILE_END)
  {
    if(fsUploadFile)
      fsUploadFile.close();
    Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
  }
}

void handleFileList()
{
  String path = "/";
  // Assuming there are no subdirectories
  Dir dir = SPIFFS.openDir(path);
  String output = "[";
  while(dir.next())
  {
    File entry = dir.openFile("r");
    // Separate by comma if there are multiple files
    if(output != "[")
      output += ",";
    output += String(entry.name()).substring(1);
    entry.close();
  }
  output += "]";
  server.send(200, "text/plain", output);
}

bool handleFileRead(String path){
  Serial.println("handleFileRead: " + path);
  if(path.endsWith("/")) path += "index.html";
 
  if( SPIFFS.exists(path)){
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, "text/html");
    file.close();
    return true;
  }
  return false;
}
