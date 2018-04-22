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

float c_l = 320.76 ;
float c_f = 33.98;
float c_r = 101.63;
float c_b = 199.89;
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
  }
 else if(inchesl < 4 && inches > 6 && inchesr > 6){  
  Serial.println("///////////////////////////// Go FRONT RIGHT MORE /////////////////////////////////////"); 
  motorFront(100); 
  }
 else if((inchesl > 6) && (inches < 4) && (inchesr < 4)){ 

     Serial.println("///////////////////////////////// TURN LEFT //////////////////////////////////////////"); 
     Serial.println(com_f);
     Serial.println(c);
     if(com_f == c_f){
      
     }
//     if(com_f == c_f){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_l)>=0){
//          com_f=c_l;
//          motorTurnleft_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//         motorTurnleft_right(75);
//        }
//        else if((com_f-c_b)>=0){
//          com_f=c_b;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnleft_right(75);
//        }
//         else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_r){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_right(75);
//        }
//        else if
//        ((com_f-c_f)<=0){
//        
//          com_f=c_f;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(90 < c < 110){
//          com_f=c_f;
//          motorTurnleft_right(75);
//      }
      
  }
// else if(inchesl > 6 && inches > 6 && inchesr < 4){  
//  Serial.println("///////////////////////////////// TURN LEFT FORNT MORE //////////////////////////////////////////"); 
//     Serial.println(com_f);
//     Serial.println(c);
//     if(com_f == c_f){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_l)>=0){
//          com_f=c_l;
//          motorTurnleft_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//         motorTurnleft_right(75);
//        }
//        else if((com_f-c_b)>=0){
//          com_f=c_b;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnleft_right(75);
//        }
//         else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnleft_left(75);
//        }
//      }
////      else if((com_f <= (c_r+2))||(com_f >=(c_r-2)) ){
//        else if(com_f >= c_r ){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_left(75);
//        }
//        else if(90 < c < 105){
//          com_f=c_f;
//          motorTurnleft_right(75);
//      }
//      } 
//  }//3
//     else if((inchesl > 6) && (inches < 4) && (inchesr > 4)){ 
//
//     Serial.println("///////////////////////////////// TURN LEFT LEFT&RIGHT MORE/////////////////////////////////////////"); 
//     
//     if(com_f == c_f){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_l)>=0){
//          com_f=c_l;
//          motorTurnleft_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//         motorTurnleft_right(75);
//        }
//        else if((com_f-c_b)>=0){
//          com_f=c_b;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnleft_right(75);
//        }
//         else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_r){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_left(75);
//        }
//      }
//
//      
//  }//7
//
//       else if((inchesl > 6) && (inches > 4) && (inchesr > 4)){ 
//
//     Serial.println("///////////////////////////////// TURN LEFT LEFT&FORNT&RIGHT MORE//////////////////////////////////////////"); 
//     
//     if(com_f == c_f){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_l)>=0){
//          com_f=c_l;
//          motorTurnleft_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//         motorTurnleft_right(75);
//        }
//        else if((com_f-c_b)>=0){
//          com_f=c_b;
//          motorTurnleft_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnleft_right(75);
//        }
//         else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnleft_left(75);
//        }
//      }c
//      else if(com_f == c_r){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_right(75);
//        }
//        else if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnleft_left(75);
//        }
//      }
//       else if(90 < c < 105){
//          com_f=c_f;
//          motorTurnleft_right(75);
//      }
//
//      
//  }//8


// else if((inchesl < 4 )&& (inches < 6) && (inchesr > 6)){ 
//     Serial.println("///////////////////////////////// TURN RIGHT //////////////////////////////////////////"); 
//     
//     if(com_f == c_f){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnright_right(75);
//        }
//        else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnright_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//         motorTurnright_right(75);
//        }
//        else if((com_f-c_f)>=0){
//          com_f=c_f;
//          motorTurnright_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnright_right(75);
//        }
//         else if((com_f-c_l)>=0){
//          com_f=c_l;
//          motorTurnright_left(75);
//        }
//      }
//      else if(com_f == c_r){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//          motorTurnright_right(75);
//        }
//        else if((com_f-c_b)<=0){
//          com_f=c_b;
//          motorTurnright_left(75);
//        }
//      }
//  }//6
// else if((inchesl < 4) && (inches < 4) && (inchesr < 4)){  
//     Serial.println("///////////////////////////////// TURN BACK //////////////////////////////////////////"); 
//     
//     if(com_f == c_f){
//        if((com_f-c_b)<=0){
//          com_f=c_b;
//          motorTurnback_right(75);
//        }
//        else if((com_f-c_b)>=0){
//          com_f=c_b;
//          motorTurnback_left(75);
//        }
//      }
//      
//      else if(com_f == c_l){
//        if((com_f-c_r)<=0){
//          com_f=c_r;
//          motorTurnback_right(75);
//        }
//        else if((com_f-c_r)>=0){
//          com_f=c_r;
//          motorTurnback_left(75);
//        }
//      }
//      else if(com_f == c_b){
//        if((com_f-c_f)<=0){
//          com_f=c_f;
//          motorTurnback_right(75);
//        }
//         else if((com_f-c_f)>=0){
//          com_f=c_f;
//          motorTurnback_left(75);
//        }
//      }
//      else if(com_f == c_r){
//        if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnback_right(75);
//        }
//        else if((com_f-c_l)<=0){
//          com_f=c_l;
//          motorTurnback_left(75);
//        }
//      }
//   
//  }//4
   
 else { 
       Serial.println("////////////////////   Else  //////////////////////");
       Serial.println(com_f);
     Serial.println(c);
         motorFront(100);  
  }//other 
}

void _compass() {
  c = compass.read();
}

void motorFront(int speed){

Serial.println("///////////////////////////////// FRONT FRONT  //////////////////////////////////////////"); 
  
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

void motorTurnleft_left(int speed){
   Serial.println("///////////////////////////////// TURN LEFT LEFT//////////////////////////////////////////"); 
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
   Serial.println("///////////////////////////////// TURN LEFT RIGHT//////////////////////////////////////////"); 
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
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com_f);
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
Serial.println("///////////////////////////////// TURN RIGHT LEFT//////////////////////////////////////////");

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
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com_f);
  }
  motorFront(100);

}

void motorTurnright_right(int speed){
Serial.println("///////////////////////////////// TURN RIGHT RIGHT//////////////////////////////////////////");

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
    Serial.print("heading: ");
    Serial.print(c);
    Serial.print(" target: ");
    Serial.println(com_f);
  }
  motorFront(100);

}
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


