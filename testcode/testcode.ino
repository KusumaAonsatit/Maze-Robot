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

float c_l = 37.00 ;
float c_f = 100.00;
float c_r = 189.00;
float c_b = 100.00;
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
 else if(inchesl < 4 && inches < 6 && inchesr < 4){  
  
  if((c-c_b)<=0){
    motorTurnback_right(75);
  }
  else{
    motorTurnback_left(75);
  }
   
  }//4
   else if(inchesl > 6 && inches < 6 && inchesr < 4){ 
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
  c = compass.read();
}

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
void motorTurnback_left(int speed){

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
    if(c <= c_b){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(c_b);
  }
}
void motorTurnback_right(int speed){

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
    if(c >= c_b){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
     break;
    }
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(c_b);
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
    if(c <= c_l){//เอาแค่ค่าน้อยกว่าหรือมากกว่าอันเดียวพอ 
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

