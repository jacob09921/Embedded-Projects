const int relay1 = 7; // selected pin
const int relay2 = 8; // selected pin

void setup() {
pinMode(relay1, OUTPUT); // setup the output of every pin
pinMode(relay2, OUTPUT); // setup the output of every pin
}

void loop() { // loop your main program 
 digitalWrite(relay1,LOW); // default program
 digitalWrite(relay2,HIGH); // default program
do { // using do while 
  delay(2000);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,LOW);
  
}while(digitalRead(relay1)== LOW);
do{
  delay(2000);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay1,LOW);
}while(digitalRead(relay2)== LOW);
}
