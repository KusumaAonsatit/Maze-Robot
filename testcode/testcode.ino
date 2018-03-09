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
//void _sonar();


int enableA = 6;
int pinA1 = 2;
int pinA2 = 3;

int enableB = 7;
int pinB1 = 4;
int pinB2 = 5;

float c_l = 38.82 ;
float c_f = 105.95;
float c_r = 192.95;
float c_b = 315.97;
float com_f = c_f;
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
  int sumL=0,sumM=0,sumR=0;
  for(int i=0;i<20;i++){
     sumM += sonar.ping_in();
     sumL += sonarl.ping_in();
     sumR += sonarr.ping_in();
  }
  inches = sumM/20;
  inchesl = sumL/20;
  inchesr = sumR/20;
  
  Serial.print("left  ");
  Serial.print(inchesl);
  Serial.print("  mid  ");
  Serial.print(inches);
  Serial.print("  right  ");
  Serial.println(inchesr);
  
 //prin();
 _compass();
// _sonar();
  
 if((inchesl < 4) && (inches > 6 )&& (inchesr < 4) ){
  Serial.println("///////////////////////////////// Go FRONT //////////////////////////////////////////"); 
  motorFront(100);  
  }//1
// else if(inchesl < 4 && inches > 6 && inchesr > 6){  
//  motorFront(100); 
//  }//2
// else if(inchesl > 6 && inches > 6 && inchesr < 4){  
//  motorFront(100); 
//  }//3
 else if((inchesl < 4) && (inches < 4) && (inchesr < 4)){  
     Serial.println("///////////////////////////////// TURN BACK //////////////////////////////////////////"); 
     if(com_f == c_f){
        if((com_f-c_b)<=0){
          com_f=c_b;
          motorTurnback_right(75);
        }
        else{
          com_f=c_b;
          motorTurnback_left(75);
        }
      }
      else if(com_f == c_l){
        if((com_f-c_r)<=0){
          com_f=c_r;
          motorTurnback_right(75);
        }
        else{
          com_f=c_r;
          motorTurnback_left(75);
        }
      }
      else if(com_f == c_b){
        if((com_f-c_f)<=0){
          com_f=c_f;
          motorTurnback_right(75);
        }
        else{
          com_f=c_f;
          motorTurnback_left(75);
        }
      }
      else if(com_f == c_r){
        if((com_f-c_l)<=0){
          com_f=c_l;
          motorTurnback_right(75);
        }
        else{
          com_f=c_l;
          motorTurnback_left(75);
        }
      }
   
  }//4
//   else if(inchesl > 6 && inches < 6 && inchesr < 4){ 
//  motorTurnleft(75); 
//  }//5
// else if(inchesl < 4 && inches < 6 && inchesr > 6){ 
//   if((c > 270) && (c < 360)){
//  motorTurnright(100);
//  }//6
 else { 
       Serial.println("////////////////////   Else  //////////////////////");
         motorFront(100);  
  }//other 
}

void _compass() {
  c = compass.read();
}


void motorFront(int speed){
  
  // Motor A left
  
          analogWrite(enableA, speed-10);

          digitalWrite(pinA1, LOW);

          digitalWrite(pinA2, HIGH);

 // Motor B

    analogWrite(enableB, speed+20); 

    digitalWrite(pinB1,LOW);

    digitalWrite(pinB2,HIGH);
  
    //delay(300);
}


//void motorFront(int speed){
//  
//  // Motor A left
//  
//          analogWrite(enableA, speed-10);
//
//          digitalWrite(pinA1, HIGH);
//
//          digitalWrite(pinA2, LOW);
//
// // Motor B
//
//    analogWrite(enableB, speed+20); 
//
//    digitalWrite(pinB1, HIGH);
//
//    digitalWrite(pinB2, LOW);
//  
//    //delay(300);
//
////    _sonar();
//    
//}
void motorTurnback_left(int speed){


Serial.println("///////////////////////////////// TURN BACK LEFT//////////////////////////////////////////"); 
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
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com_f);

//    Serial.print("left  ");
//    Serial.print(inchesl);
//    Serial.print("  mid  ");
//    Serial.print(inches);
//    Serial.print("  right  ");
//    Serial.println(inchesr);
      }
}
void motorTurnback_right(int speed){

  Serial.println("///////////////////////////////// TURN BACK RIGHT//////////////////////////////////////////"); 

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
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com_f);

//    Serial.print("left  ");
//    Serial.print(inchesl);
//    Serial.print("  mid  ");
//    Serial.print(inches);
//    Serial.print("  right  ");
//    Serial.println(inchesr);
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

