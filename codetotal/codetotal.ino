#include <NewPing.h>
#include <HMC5983.h>
#include <Wire.h>
//------------------SONAR-------------------------//
NewPing sonar(11, 10); //trig,echo
NewPing sonarl(9, 8);
NewPing sonarr(13, 12);
//------------------LED-------------------------//
int ledPinl = 22;
int ledPinf = 24;
int ledPinr = 26;
boolean bLedOn = true;
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
float cf = 33.98;
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

  compass.begin(); // use "true" if you need some debug information

  pinMode(ledPinl, OUTPUT);
  pinMode(ledPinf, OUTPUT);
  pinMode(ledPinr, OUTPUT);
}

void loop() {

 _compass();
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
     if(lest_cf <= com_f <= most_cf){
        if((com_f-cl)<=0){
          com_f=cl;
          motorTurnleft_right(75);
        }
        else if((com_f-cl)>=0){
          com_f=cl;
          motorTurnleft_left(75);
        }
      }
      else if(lest_cl <= com_f <= most_cl){
        if((com_f-cb)<=0){
          com_f=cb;
         motorTurnleft_right(75);
        }
        else if((com_f-cb)>=0){
          com_f=cb;
          motorTurnleft_left(75);
        }
      }
      else if(lest_cb <= com_f <= most_cb){
        if((com_f-cr)<=0){
          com_f=cr;
          motorTurnleft_right(75);
        }
         else if((com_f-cr)>=0){
          com_f=cr;
          motorTurnleft_left(75);
        }
      }
      else if(lest_cl <= com_f <= most_cl){
        if((com_f-cf)<=0){
          com_f=cf;
          motorTurnleft_right(75);
        }
        else if
        ((com_f-cf)<=0){
        
          com_f=cf;
          motorTurnleft_left(75);
        }
      }

  }
//  else if(inchesl > 6 && inches > 6 && inchesr < 4){  
//    Serial.println("////////////////////////////// TURN LEFT LEFT&FORNT MORE /////////////////////////////");
//  }
//  else if((inchesl > 6) && (inches < 4) && (inchesr > 4)){ 
//    Serial.println("///////////////////////////////// TURN LEFT LEFT&RIGHT MORE///////////////////////////");
//  }
//  else if((inchesl > 6) && (inches > 4) && (inchesr > 4)){ 
//    Serial.println("///////////////////////////////// TURN LEFT LEFT&FORNT&RIGHT MORE/////////////////////");
//  }
//  else if((inchesl < 4 )&& (inches < 6) && (inchesr > 6)){ 
//    Serial.println("////////////////////////////// TURN RIGHT RIGHT MORE /////////////////////////////////");
//  }
//  else if((inchesl < 4) && (inches < 4) && (inchesr < 4)){  
//    Serial.println("///////////////////////////////// TURN BACK //////////////////////////////////////////");
//  }
  else { 
    Serial.println("//////////////////////////////////// Else ////////////////////////////////////////////");
    motorFront(100); 
  }
}

//Function Compass
void _compass() {
  c = compass.read();
}

void motorFront(int speed){
    Serial.println("----------------------------------- FRONT FRONT -------------------------------------"); 
    digitalWrite(ledPinf, bLedOn);
  // Motor A left
    analogWrite(enableA, speed-10);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
 // Motor B
    analogWrite(enableB, speed+20); 
    digitalWrite(pinB1,LOW);
    digitalWrite(pinB2,HIGH);
}

void motorTurnleft_left(int speed){
    Serial.println("----------------------------------- TURN LEFT LEFT -----------------------------------"); 
    digitalWrite(ledPinl, bLedOn); 
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
    digitalWrite(ledPinl, bLedOn);
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
    digitalWrite(ledPinr, bLedOn);
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
    digitalWrite(ledPinr, bLedOn);
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
    digitalWrite(ledPinl, bLedOn);
    digitalWrite(ledPinf, bLedOn);
    digitalWrite(ledPinr, bLedOn);
    
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
    digitalWrite(ledPinl, bLedOn);
    digitalWrite(ledPinf, bLedOn);
    digitalWrite(ledPinr, bLedOn);
    
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


