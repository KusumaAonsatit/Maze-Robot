#include <NewPing.h>
#include <HMC5983.h>
#include <Wire.h>

//Tell the Arduino where the sensor is hooked up
NewPing sonar(11, 10); //trig,echo
NewPing sonarl(9, 8);
NewPing sonarr(13, 12);

void motorFront(int speed);
void motorFront1(int speed);
void motorTurnback(int speed);
void motorTurnright(int speed);
void motorTurnleft(int speed);


int enableA = 6;
int pinA1 = 2;
int pinA2 = 3;

int enableB = 4;
int pinB1 = 5;
int pinB2 = 7;

float c;
float com;

long inches,inchesl,inchesr;

HMC5983 compass;

void setup() {
  Serial.begin(9600);
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);

  compass.begin(); // use "true" if you need some debug information
}

void loop() {


//Ping the sensor and determine the distance in inches
  inches = sonar.ping_in();
  inchesl = sonarl.ping_in();
  inchesr = sonarr.ping_in();

  
 //prin();
 _compass();
  
 if((inchesl < 4) && (inches > 6 )&& (inchesr < 4) ){ 
  motorFront(100);  
  }//1
// else if(inchesl < 4 && inches > 6 && inchesr > 6){  
//  motorFront(100); 
//  }//2
// else if(inchesl > 6 && inches > 6 && inchesr < 4){  
//  motorFront(100); 
//  }//3
// else if(inchesl < 4 && inches < 6 && inchesr < 4){  
//  com = c-180; 
//  motorTurnback(100); 
//  }//4
 else if(inchesl > 6 && inches < 6 && inchesr < 4){ 
   if((c > 270) && (c < 360)){
    com = (c + 30) - 360;
   }
   else if ((c > 0) && (c > 90)){
    com = 90 - c;
    com = 360 - c;
   }
   else{
    com = c - 90;
   }
  motorTurnleft(75); 
  }//5
// else if(inchesl < 4 && inches < 6 && inchesr > 6){ 
//   if((c > 270) && (c < 360)){
 
//  motorTurnright(100);
//  }//6
 else { 
  motorFront(100);  
  }//other 

}

void _compass() {
 // float c = -999;
  c = compass.read();
 // delay(500);
}
//void prin(){
//  Serial.print("Left : ");
//  Serial.print(inchesl);
//  Serial.print("   Front : ");
//  Serial.print(inches);
//  Serial.print("   Right : ");
//  Serial.println(inchesr);
//  Serial.print("   compass : ");
//  Serial.println(c);
//  delay(100);
//}
void motorFront(int speed){
  
  // Motor A left
  
          analogWrite(enableA, speed-3);

          digitalWrite(pinA1, LOW);

          digitalWrite(pinA2, HIGH);

 // Motor B

    analogWrite(enableB, speed+20); 

    digitalWrite(pinB1, LOW);

    digitalWrite(pinB2, HIGH);
  
    //delay(300);
}
void motorTurnback(int speed){

  while(c!=com){
    // Motor A 
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
  }

}
void motorTurnleft(int speed){
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
    if(c >= com){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }

    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com);
  }
  motorFront(100);
}

void motorTurnright(int speed){

  while(c!=com){
    // Motor A
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2,HIGH );
    // Motor B          
    analogWrite(enableB, speed); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW); 
  }

}
/*********************************************************************************
 if((c > 270) && (c < 360)){
  com = (c + 30) - 360;
 }
 else if ((c > 0) && (c > 90)){
  com = 90 - x;
  x = 360 - x;
 }
 else{
  com = c - 90;
 }
/*********************************************************************************
  if((c > 270) && (c < 360)){
  com = (c + 30) - 360;
 }
 else if ((c > 0) && (c > 90)){
  com = 90 - x;
  x = 360 - x;
 }
 else{
  com = c + 90;
 }
 */
