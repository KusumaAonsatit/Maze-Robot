int enableA = 6;
int pinA1 = 2;
int pinA2 = 3;

int enableB = 7;
int pinB1 = 4;
int pinB2 = 5;
//int speedPinA = 6; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์ 
//Counter speed sensor-----------------------------------------------------------------------//
    //const byte interruptPinL = 18;
    //const byte interruptPinR = 19;
    
//speed ไว้สำหรับปรัความเร็วมอเตอร์
int speed = 10;
long Left,Right;

void setup(){
  Serial.begin(9600);
pinMode(enableA, OUTPUT);
pinMode(pinA1, OUTPUT);
pinMode(pinA2, OUTPUT);

pinMode(enableB, OUTPUT);
pinMode(pinB1, OUTPUT);
pinMode(pinB2, OUTPUT);
}
void loop(){
 //peed = Serial.read(); 
 // analogWrite(speedPinA, speed); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง

  motorFront(100);
  
//delay(5000);
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
  
    //delay(300);
}
