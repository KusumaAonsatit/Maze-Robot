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
boolean bLedOn = true;
boolean bLedOff = false;
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

  compass.begin(); // use "true" if you need some debug information
//------------------LED-------------------------//
  pinMode(ledPinl, OUTPUT);
  pinMode(ledPinf, OUTPUT);
  pinMode(ledPinr, OUTPUT);
  
//------------------SONAR-------------------------//  
  pinMode(pingPin1, OUTPUT);
  pinMode(inPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(inPin2, INPUT);
  pinMode(pingPin3, OUTPUT);
  pinMode(inPin3, INPUT);
}

void loop() {

long duration,duration2,duration3;
//int cmR, cmF, cmL;

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


  Serial.print("left  ");
  Serial.print(inchesl);
  Serial.print("  mid  ");
  Serial.print(inches);
  Serial.print("  right  ");
  Serial.println(inchesr);
  
  if((inchesl < 4) && (inches > 6 )&& (inchesr < 4) ){
    Serial.println("///////////////////////////////// Go FRONT ///////////////////////////////////////////");
    motorFront(100); 
  }
  else if(inchesl < 4 && inches > 6 && inchesr > 6){  
    Serial.println("///////////////////////////// Go FRONT RIGHT MORE ////////////////////////////////////");
    motorFront(100); 
  }
  else if((inchesl > 6) && (inches < 4) && (inchesr < 4)){ 
    Serial.println("/////////////////////////////// TURN LEFT LEFT MORE //////////////////////////////////"); 
    motorTurnleft(100);  
  }
  else if(inchesl > 6 && inches > 6 && inchesr < 4){  
    Serial.println("////////////////////////////// TURN LEFT LEFT&FORNT MORE /////////////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl > 6) && (inches < 4) && (inchesr > 4)){ 
    Serial.println("///////////////////////////////// TURN LEFT LEFT&RIGHT MORE///////////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl > 6) && (inches > 4) && (inchesr > 4)){ 
    Serial.println("///////////////////////////////// TURN LEFT LEFT&FORNT&RIGHT MORE/////////////////////");
    motorTurnleft(100); 
  }
  else if((inchesl < 4 )&& (inches < 6) && (inchesr > 6)){ 
    Serial.println("////////////////////////////// TURN RIGHT RIGHT MORE /////////////////////////////////");
    motorTurnright(100);
  }
  else if((inchesl < 4) && (inches < 4) && (inchesr < 4)){  
    Serial.println("///////////////////////////////// TURN BACK //////////////////////////////////////////");
    motorTurnback(100);
  }
  else { 
    Serial.println("//////////////////////////////////// Else ////////////////////////////////////////////");
    motorFront(100); 
  }
}
long microsecondsToCentimeters(long microseconds){
      return microseconds / 29 / 2;
}

void motorFront(int speed){
    Serial.println("----------------------------------- FRONT FRONT -------------------------------------"); 
    digitalWrite(ledPinl, bLedOff);
    digitalWrite(ledPinf, bLedOn);
    digitalWrite(ledPinr, bLedOff);
    bLedOn = !bLedOn;
    
  // Motor A left
    analogWrite(enableA, speed-10);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
 // Motor B
    analogWrite(enableB, speed+20); 
    digitalWrite(pinB1,LOW);
    digitalWrite(pinB2,HIGH);
    
//    digitalWrite(ledPinf, bLedOff);
}

void motorTurnleft(int speed){
    Serial.println("----------------------------------- TURN LEFT -----------------------------------------"); 
    digitalWrite(ledPinl, bLedOn);
    digitalWrite(ledPinf, bLedOff);
    digitalWrite(ledPinr, bLedOff);
    bLedOn = !bLedOn;
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
    
//    digitalWrite(ledPinl, bLedOff);
}


void motorTurnright(int speed){
    Serial.println("----------------------------------- TURN RIGHT -----------------------------------------");
    digitalWrite(ledPinl, bLedOff);
    digitalWrite(ledPinf, bLedOff);
    digitalWrite(ledPinr, bLedOn);
    bLedOn = !bLedOn;
    // Motor A
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2,HIGH );
    // Motor B          
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW); 
    
//    digitalWrite(ledPinr, bLedOff);
}

void motorTurnback(int speed){

    Serial.println("----------------------------------- TURN BACK -----------------------------------------"); 
    digitalWrite(ledPinl, bLedOn);
    digitalWrite(ledPinf, bLedOn);
    digitalWrite(ledPinr, bLedOn);
    bLedOn = !bLedOn;
    
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
    
//    digitalWrite(ledPinl, bLedOff);
//    digitalWrite(ledPinf, bLedOff);
//    digitalWrite(ledPinr, bLedOff);
}

