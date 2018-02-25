#include <NewPing.h>
#include <HMC5983.h>
#include <Wire.h>

//Tell the Arduino where the sensor is hooked up
NewPing sonar(11, 10); //trig,echo
NewPing sonarl(9, 8);
NewPing sonarr(13, 12);

void motorFront(int speed);
void motorTurnback(int speed);
void motorTurnright(int speed);
void motorTurnleft(int speed);

// calibreat //
//float v0 = 0;
float v90 = 82;
float v180 = 180;
float v270 = 278;
/////////////////////////////////

int enableA = 6;
int pinA1 = 2;
int pinA2 = 3;

int enableB = 7;
int pinB1 = 4;
int pinB2 = 5;

long inches,inchesl,inchesr;

float com=0;
float c = -999;


char ch;
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
   _compass();
  inches = sonar.ping_in();  // front
  inchesl = sonarl.ping_in(); // left
  inchesr = sonarr.ping_in(); // Right
  
  
  Serial.print("        Left = ");
  Serial.print(inchesl);
  Serial.print("    Front = ");
  Serial.print(inches);
  Serial.print("    Right = ");
  Serial.println(inchesr);



 
  
   
   ch = Serial.read();
   if(ch == 'F'){
      motorFront(70);
      delay(1000);
   }
   if(ch == 'L'){
      //while(c!=com){
          motorLeft(80);
           delay(1000);
           ch = 'S';
      //}
   }
   if(ch == 'l'){
      motorLeft_Smoot(70);
       delay(1000);
   }
   if(ch =='R'){
      motorRight(80);
       delay(1000);
       ch = 'S';
   }
   if(ch == 'r'){
      motorRight_Smoot(70);
       delay(1000);
   }
   if(ch == 'S'){
      motorSTOP();
   }
   if(ch == 'G'){
      motorBack(70);
   }
   if(ch == 'B'){
       if(c<77){
           com = 77 - c;
           com = 360 - com;
       }
       else
          com = c - 77;
       //com = c - 180.00;
       motorTurnBack(80);
   }
   if(ch == 'b'){
       if(c<180){
           com = 180 - c;
           com = 360 - com;
       }
       else
          com = c - 180;
       //com = c - 180.00;
       motorTurnBack(61');
   }

    

   
//Ping the sensor and determine the distance in inches
  
  /*
//If the robot detects an obstacle less than four inches away, it will back up, then turn left; if no obstacle is detected, it will go forward
 
 if(inchesl < 5 && inches > 6 && inchesr < 5 ){ //Front1
      motorFront(100);
  }
  
 else if(inchesl < 6 && inches > 6 && inchesr > 6){  //Front2
      motorFront(100); 
  }
  
 else if((inchesl < 4) && (inches < 6) && (inchesr < 4)){  //Turnback
     com = c-180; 
     motorTurnback(100); 
  }
  
 else { //other 
  motorFront(100);  
  }

  */
}

void _compass() {
  
  c = compass.read();
  
  Serial.print("compass = ");
  Serial.print(c);
  //delay(500);
}



void motorTurnBack(int speed){
  Serial.print("COM = ");
  Serial.println(com);
  while(1){
      _compass();
      Serial.print("C = ");
      Serial.print(c);
      Serial.print("  COM = ");
      Serial.println(com);
      motorRight(speed);
      
      if(c > (com-2.5) && c < (com+2.5)){
          break;
      }
  }
  Serial.println("///////////////////////////STOP/////////////////////////////");
  motorSTOP();
  delay(500000);
  }





////////////////////Standard Function///////////////////////
void motorBack(int speed){
      // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B Right
    analogWrite(enableB, speed + 20); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);
    
}
void motorFront(int speed){

    // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B Right
    analogWrite(enableB, speed + 15); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
    
    //delay(50);
}


void motorLeft_Smoot(int speed){
    // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B Right
    analogWrite(enableB, speed + 20 + 10); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
}
void motorLeft(int speed){
   analogWrite(enableA, speed);
    digitalWrite(pinA1, HIGH);
    digitalWrite(pinA2, LOW);
    // Motor B Right
    analogWrite(enableB, speed + 22); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
}



void motorRight_Smoot(int speed){
    // Motor A left
    analogWrite(enableA, speed + 10);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B Right
    analogWrite(enableB, speed + 20 ); 
    digitalWrite(pinB1, LOW);
    digitalWrite(pinB2, HIGH);
}
void motorRight(int speed){
   // Motor A left
    analogWrite(enableA, speed);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B Right
    analogWrite(enableB, speed + 20 ); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);
}

void motorSTOP(){
   analogWrite(enableA,0);
    digitalWrite(pinA1, LOW);
    digitalWrite(pinA2, HIGH);
    // Motor B Right
    analogWrite(enableB,0); 
    digitalWrite(pinB1, HIGH);
    digitalWrite(pinB2, LOW);
}
////////////////END  Standard  Function ///////////////////////
 float CLB(float c){
      float ans=0;
      if( c >= 0 && c <= v90)
          ans = (c * 90)/(v90 - 0);
          
      else if( c >= v90 && c <= v180)
          ans = 90 + (c * 90)/(v180 - v90);
          
      else if( c >= v180 && c <= v270)
          ans = 180 + (c * 90)/(v270 - v180);
          
      else if( c >= v270 && c <= 360 )
          ans = 270 + (c * 90)/(360 - v270);


      return ans;
     

     
}


