const int gear1 = 8; // input 1
const int gear2 = 7; // input 2
const int gear3 = 6; // input 3
const int gear4 = 5; // input 4
const int rxPin = 2;
const int txPin = 3;
const int relay = 10;
int Speed = 180;
int controls;
int num = 0 ;
int relay_stat = 0;
#include <SoftwareSerial.h>
SoftwareSerial BT(rxPin,txPin);
void setup() {

  //Motor Pins are OUTPUT
  pinMode(gear1, OUTPUT);
  pinMode(gear2, OUTPUT);
  pinMode(gear3, OUTPUT);
  pinMode(gear4, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  BT.begin(9600); 
  delay(500);
  digitalWrite(relay, HIGH);
}
void stop(){
            digitalWrite(gear1, LOW);
            digitalWrite(gear2, LOW);
            digitalWrite(gear3, LOW);
            digitalWrite(gear4, LOW);
}

void loop() {
  if (BT.available()> 0)
  {
    controls = BT.read();
    if (controls > 12){
      Serial.println("OH no");
      }
  }

  
    if (controls == 1) // this string was initialized at MIT APP inventor 
    {
      analogWrite(gear1, Speed);
      analogWrite(gear3, Speed);
      analogWrite(gear2, LOW);
      analogWrite(gear4, LOW); 
    }
    else if (controls == 2) // this string was initialized at MIT APP inventor 
    { 
      analogWrite(gear2, Speed);
      analogWrite(gear4, Speed);
      analogWrite(gear1, LOW);
      analogWrite(gear3, LOW);
  
    }
    else if (controls == 3) // this string was initialized at MIT APP inventor 
    { 
      analogWrite(gear3,Speed);
      analogWrite(gear2,Speed);
      analogWrite(gear1,LOW);
      analogWrite(gear4,LOW);
     
    }
    else if (controls == 4) // this string was initialized at MIT APP inventor 
    { 
      analogWrite(gear4, Speed);
      analogWrite(gear1, Speed);
      analogWrite(gear3, LOW);
      analogWrite(gear2, LOW);
    }
     else if (controls == 5) // this string was initialized at MIT APP inventor 
    {
   
      analogWrite(gear4, LOW);
      analogWrite(gear1, Speed);
      analogWrite(gear3, LOW);
      analogWrite(gear2, LOW);
    }
     else if (controls == 6) // this string was initialized at MIT APP inventor 
    {
     
      analogWrite(gear4, LOW);
      analogWrite(gear1, LOW);
      analogWrite(gear3, LOW);
      analogWrite(gear2, Speed);
    }
      else if (controls == 7) // this string was initialized at MIT APP inventor 
    { 
      
      analogWrite(gear4, LOW);
      analogWrite(gear1, LOW);
      analogWrite(gear3, Speed);
      analogWrite(gear2, LOW);
    }
     else if (controls == 8) // this string was initialized at MIT APP inventor 
    { 
      analogWrite(gear4, Speed);
      analogWrite(gear1, LOW);
      analogWrite(gear3, LOW);
      analogWrite(gear2, LOW);
    }
    else if (controls == 9) // this string was initialized at MIT APP inventor 
    {
      stop();
      }

    else if (controls == 10 && num == 0) {
     Speed = 0;  
     num = 1;
     controls = 0; 
    }
    else if (controls == 10 && num == 1){
      Speed = 180 ;
      controls = 9;
      num = 0;
      }
      
    else if (controls == 11 && relay_stat == 0) {
     delay(1000);
     digitalWrite(relay, LOW);
     controls = 9;
     relay_stat = 1;
    }
    else if (controls == 11 && relay_stat == 1) {
     delay(1000);
     digitalWrite(relay, HIGH);
     controls = 9;
     relay_stat = 0;
    }
     
        
    delay(100);
    Serial.print("Control Names: ");  
    Serial.println(controls);// to see the controls name and also to identify. 
    Serial.println(Speed);
  
 }
