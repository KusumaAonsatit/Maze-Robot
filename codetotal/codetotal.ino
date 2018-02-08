#include <NewPing.h>

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

long inches,inchesl,inchesr;


void setup() {
  Serial.begin(9600);
pinMode(enableA, OUTPUT);
pinMode(pinA1, OUTPUT);
pinMode(pinA2, OUTPUT);

pinMode(enableB, OUTPUT);
pinMode(pinB1, OUTPUT);
pinMode(pinB2, OUTPUT);
}

void loop() {


//Ping the sensor and determine the distance in inches
inches = sonar.ping_in();
inchesl = sonarl.ping_in();
inchesr = sonarr.ping_in();

//If the robot detects an obstacle less than four inches away, it will back up, then turn left; if no obstacle is detected, it will go forward
 if(inchesl < 5 && inches > 6 && inchesr < 5 ){ motorFront(200);  }//1
 else if(inchesl < 4 && inches < 6 && inchesr < 4){  motorTurnback(200); }//2
 else if(inchesl > 6 && inches < 10 && inchesr < 6){  motorTurnleft(240); }//3
 else if(inchesl > 6 && inches > 6 && inchesr < 10){  motorTurnleft(240);
  if(inches > 6 ){    
      motorFront1(200);
      }
 }//4
 else if(inchesl > 6 && inches < 6 && inchesr > 6){  motorTurnleft(240); }//5
 else if(inchesl > 6 && inches > 6 && inchesr > 6){  motorTurnleft1(240); 
  if(inches > 6 ){    
      motorFront1(200);
      }
 }//6
 else if(inchesl < 6 && inches < 8 && inchesr > 6){  motorTurnright(240);}
 else if(inchesl < 6 && inches < 2 && inchesr > 6){  motorTurnright1(200);}
 else if(inchesl < 6 && inches > 6 && inchesr > 6){  motorFront(255); }//8
 else { motorFront(255);  }//other 
}
void motorFront(int speed){
  
  // Motor A left
  analogWrite(enableA, speed);
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);

 // Motor B
  analogWrite(enableB, speed); 
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(50);
}
void motorFront1(int speed){
  
  // Motor A 
  
          analogWrite(enableA, speed);

          digitalWrite(pinA1, LOW);

          digitalWrite(pinA2, HIGH);

 // Motor B

   analogWrite(enableB, speed); 

  digitalWrite(pinB1, LOW);

  digitalWrite(pinB2, HIGH);
  delay(2000);
}
void motorTurnback(int speed){

  analogWrite(enableA, speed);
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);

  analogWrite(enableB, speed); 
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(2100);

}
void motorTurnleft(int speed){

  //delay(100);
  analogWrite(enableA, 0);
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);

  analogWrite(enableB, speed); 
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(1600);
}

void motorTurnleft1(int speed){

  //delay(200);
  analogWrite(enableA, 0);
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);

  analogWrite(enableB, speed); 
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  delay(1700);
  //motorFront(220);
}
void motorTurnright(int speed){
  
//delay(100);
  analogWrite(enableA, speed);
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2,HIGH );
          
  analogWrite(enableB, 0); 
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);       
  delay(1700);
}
void motorTurnright1(int speed){
  
//delay(100);
  analogWrite(enableA, speed);
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2,HIGH );
          
  analogWrite(enableB, 0); 
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);       
  delay(1800);
}
