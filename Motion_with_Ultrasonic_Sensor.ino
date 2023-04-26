#include <Servo.h> // an import library from arduino 
#include <LiquidCrystal_I2C.h> // an import library from arduino 
#include <NewPing.h> // an import library from arduino app
const int pir = 7; // pin from arduino keep in mind
const int green = 6; // pin from arduino keep in mind
const int red = 5; // pin from arduino keep in mind
int distance_cm, duration_us; // created variable 
LiquidCrystal_I2C lcd(32, 16, 2); // store the pin of the Liquid Crystal Display
Servo servo; // creating Variable from class called Servo
NewPing ultrasonicSensor(9,8,400); // creating Variable from class called Servo
int num;

void closeGate(){ // function called closeGate, it aims display closed program
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0,0);   
  lcd.print("GATE CLOSED!"); 
  digitalWrite(red, HIGH); // led on , 
  digitalWrite(green, LOW); // led off
}


void openGate(){ // function called openGate, it aims display open program
  lcd.clear();
  lcd.init();   
  lcd.backlight();
  lcd.setCursor(0,0);   
  lcd.print("GATE IS OPENING"); 
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);    
  
      }

void ledBlink(){ // a function that let the led blink many times
  for (int i =0 ; i < 4; i++){
  digitalWrite(green, LOW);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
  delay(500);
  
        }
}


void setup() { // setup the pinmodes
  Serial.begin(9600);
  pinMode(pir, INPUT_PULLUP);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  servo.attach(10);
}
void loop(){ // function loop for your main, in other words it loop every times you execute the logic of your program
  int sensorValue = digitalRead(pir);
  distance_cm = ultrasonicSensor.ping_cm();
  if (sensorValue == HIGH){
        openGate();
       servo.write(120);      
        num = 1;
       delay(2000);
    if (distance_cm < 20 && num == 1 ) {
      servo.write(120);       
      lcd.init();   
      lcd.backlight();
      lcd.setCursor(0,0);   
      lcd.print("SOMEONE IS ");
      lcd.setCursor(0,1);   
      lcd.print("BLOCKING");
      ledBlink();
      num = 0 ;           
        }   
               
  }  
    else {    
      closeGate();
      servo.write(0);
      num = 0;
      
    }
   Serial.print("Distance: ");
  Serial.println(distance_cm);
  Serial.println(sensorValue);
}
