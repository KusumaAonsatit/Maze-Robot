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

long inches,inchesl,inchesr;

float com;
float c = -999;

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

   if (c == -999) {
    Serial.println("Reading error, discarded");
  } else {
    Serial.println(c);
  }
  
//If the robot detects an obstacle less than four inches away, it will back up, then turn left; if no obstacle is detected, it will go forward
 if(inchesl < 5 && inches > 6 && inchesr < 5 ){ 
  motorFront(100);  
  }//Front1
 else if(inchesl < 6 && inches > 6 && inchesr > 6){  
  motorFront(100); 
  }//Front2
 else if(inchesl > 6 && inches > 6 && inchesr < 6){  
  motorFront(100); 
  }//Front3
 else if(inchesl < 4 && inches < 6 && inchesr < 4){  
  com = c-180; 
  motorTurnback(100); 
  }//Turnback4
 else { 
  motorFront(100);  
  }//other 
}

void _compass() {
  
  c = compass.read();
 
  //delay(500);
}

void motorFront(int speed){
  
    // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B
    analogWrite(enableB, speed + 20); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
    
    delay(50);
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


