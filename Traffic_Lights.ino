#include <Servo.h>
const int relay1 = 7;
const int relay2 = 8;
const int relay3 = 9;
const int pLed = 11; 
Servo servo;
void setup() {
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(pLed, OUTPUT);
servo.attach(10);
}

void loop() {
 digitalWrite(relay1,LOW); // light the Green
 digitalWrite(relay2,HIGH);
 digitalWrite(relay3, HIGH);
 digitalWrite(pLed, LOW);
 servo.write(120);
do {
  delay(10000);
  digitalWrite(relay1,HIGH);
  delay(100);
  digitalWrite(relay2,LOW); // LIGHT THE YELLOW
  servo.write(120);
  
}while(digitalRead(relay1)== LOW);
do{
  delay(3000);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,LOW); // LIGHT THE RED
  servo.write(0);
  digitalWrite(pLed, HIGH);
}while(digitalRead(relay2)== LOW);

do{
  delay(10000);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay1,LOW);
  digitalWrite(pLed, LOW); // LIGHT THE GREEN
  servo.write(120);
} while (digitalRead(relay3)== LOW); 
}
