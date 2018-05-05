#include <NewPing.h>
#include <HMC5983.h>
#include <Wire.h>
//------------------SONAR-------------------------//
const int pingPin1 = 13;
int inPin1 = 12;
const int pingPin2 = 11;
int inPin2 = 10;
const int pingPin3 = 9;
int inPin3 = 8;
//------------------LED-------------------------//
int ledPinl = 22;
int ledPinf = 24;
int ledPinr = 26;
//------------------MOTOR-------------------------//
void motorFront(int speed);
void motorFront1(int speed);
void motorTurnback(int speed);
void motorTurnright(int speed);
void motorTurnleft(int speed);
int enableA = 6;
int pinA1 = 2;
int pinA2 = 3;
int enableB = 7;
int pinB1 = 4;
int pinB2 = 5;
//-----------------COMPASS-----------------------//
HMC5983 compass;
float cl = 320.76 ;
float cf = 317.91;
float cr = 101.63;
float cb = 199.89;
float lest_cl = cl - 5;
float lest_cf = cf - 5;
float lest_cr = cr - 5;
float lest_cb = cb - 5;
float most_cl = cl + 5;
float most_cf = cf + 5;
float most_cr = cr + 5;
float most_cb = cb + 5;
float com_f = cf;
float c;
long inches,inchesl,inchesr;

void setup() {
  Serial.begin(9600);
//------------------MOTOR-------------------------//
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
//------------------SONAR-------------------------//  
  pinMode(pingPin1, OUTPUT);
  pinMode(inPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(inPin2, INPUT);
  pinMode(pingPin3, OUTPUT);
  pinMode(inPin3, INPUT);
  
  compass.begin(); // use "true" if you need some debug information

  pinMode(ledPinl, OUTPUT);
  pinMode(ledPinf, OUTPUT);
  pinMode(ledPinr, OUTPUT);
}

void loop() {

long duration,duration2,duration3;

digitalWrite(pingPin1, LOW);
digitalWrite(pingPin1, HIGH);
digitalWrite(pingPin1, LOW);
duration = pulseIn(inPin1, HIGH);

digitalWrite(pingPin2, LOW);
digitalWrite(pingPin2, HIGH);
digitalWrite(pingPin2, LOW);
duration2 = pulseIn(inPin2, HIGH);

digitalWrite(pingPin3, LOW);
digitalWrite(pingPin3, HIGH);
digitalWrite(pingPin3, LOW);
duration3 = pulseIn(inPin3, HIGH);

inchesr= microsecondsToCentimeters(duration);
inches= microsecondsToCentimeters(duration2);
inchesl= microsecondsToCentimeters(duration3);

 _compass();
  Serial.print("left  ");
  Serial.print(inchesl);
  Serial.print("  mid  ");
  Serial.print(inches);
  Serial.print("  right  ");
  Serial.println(inchesr);
  
  if((inchesl < 10) && (inches > 15 )&& (inchesr < 10) ){
    Serial.println("///////////////////////////////// Go FRONT ///////////////////////////////////////////");
    motorFront(120); 
  }
  else if(inchesl < 10 && inches > 15 && inchesr > 15){  
    Serial.println("///////////////////////////// Go FRONT RIGHT MORE ////////////////////////////////////");
    motorFront(120); 
  }
  else if((inchesl > 15) && (inches < 10) && (inchesr < 10)){ 
    Serial.println("/////////////////////////////// TURN LEFT LEFT MORE //////////////////////////////////"); 
    motorTurnleft(100);  
  }
  else if(inchesl > 15 && inches > 15 && inchesr < 10){  
    Serial.println("////////////////////////////// TURN LEFT LEFT&FORNT MORE /////////////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl > 15) && (inches < 10) && (inchesr > 15)){ 
    Serial.println("///////////////////////////////// TURN LEFT LEFT&RIGHT MORE///////////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl > 15) && (inches > 15) && (inchesr > 15)){ 
    Serial.println("///////////////////////////////// TURN LEFT LEFT&FORNT&RIGHT MORE/////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl < 10 )&& (inches < 10) && (inchesr > 15)){ 
    Serial.println("////////////////////////////// TURN RIGHT RIGHT MORE /////////////////////////////////");
    motorTurnright(100);
  }
  else if((inchesl < 10) && (inches < 10) && (inchesr < 10)){  
    Serial.println("///////////////////////////////// TURN BACK //////////////////////////////////////////");
    motorTurnback(100);
  }
  else { 
    Serial.println("//////////////////////////////////// Else ////////////////////////////////////////////");
    motorFront(120); 
  }
}

long microsecondsToCentimeters(long microseconds){
      return microseconds / 29 / 2;
}

//Function Compass
void _compass() {
  c = compass.read();
}

void motorFront(int speed){
    Serial.println("----------------------------------- FRONT FRONT -------------------------------------"); 
    digitalWrite(ledPinl, LOW);
    digitalWrite(ledPinf, HIGH);
    digitalWrite(ledPinr, LOW);
    
  // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
 // Motor B
    analogWrite(enableB, speed+20); 
    digitalWrite(pinB1,LOW);
    digitalWrite(pinB2,HIGH);
}

void motorTurnleft_left(int speed){
    Serial.println("----------------------------------- TURN LEFT LEFT -----------------------------------"); 
    digitalWrite(ledPinl, HIGH);
    digitalWrite(ledPinf, LOW);
    digitalWrite(ledPinr, LOW);
     
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
    
  while(1){
    _compass();
    if(c <= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
  }
  motorFront(100);
}

void motorTurnleft_right(int speed){
    Serial.println("----------------------------------- TURN LEFT RIGHT -----------------------------------"); 
    digitalWrite(ledPinl, HIGH);
    digitalWrite(ledPinf, LOW);
    digitalWrite(ledPinr, LOW);
    
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);
    
  while(1){
    _compass();
    if(c <= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
  }
  motorFront(100);
}
void motorTurnright_left(int speed){
    Serial.println("----------------------------------- TURN RIGHT LEFT -----------------------------------");
    digitalWrite(ledPinl, LOW);
    digitalWrite(ledPinf, LOW);
    digitalWrite(ledPinr, HIGH);
    
    // Motor A
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2,HIGH );
    // Motor B          
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW); 

while(1){
    _compass();
    if(c <= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
  }
  motorFront(100);
}

void motorTurnright_right(int speed){
    Serial.println("----------------------------------- TURN RIGHT RIGHT -----------------------------------");
    digitalWrite(ledPinl, LOW);
    digitalWrite(ledPinf, LOW);
    digitalWrite(ledPinr, HIGH);
    
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);

while(1){
    _compass();
    if(c >= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
  }
  motorFront(100);
}
void motorTurnback_left(int speed){

    Serial.println("----------------------------------- TURN BACK LEFT -----------------------------------"); 
    digitalWrite(ledPinl, HIGH);
    digitalWrite(ledPinf, HIGH);
    digitalWrite(ledPinr, HIGH);
    
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);

   while(1){
    _compass();
//    _sonar();
    if(c <= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
      }
}
void motorTurnback_right(int speed){

    Serial.println("----------------------------------- TURN BACK RIGHT -----------------------------------"); 
    digitalWrite(ledPinl, HIGH);
    digitalWrite(ledPinf, HIGH);
    digitalWrite(ledPinr, HIGH);
    
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);

   while(1){
//    _sonar();
    _compass();
    if(c >= com_f){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
//    Serial.print("heading: ");
//    Serial.print(c);
//    Serial.print(" target: ");
//    Serial.println(com_f);
    Serial.print("left  ");
    Serial.print(inchesl);
    Serial.print("  mid  ");
    Serial.print(inches);
    Serial.print("  right  ");
    Serial.println(inchesr);
  }
}

