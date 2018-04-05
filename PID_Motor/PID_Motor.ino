  // Motor A Left
    int dir1PinA = 2;
    int dir2PinA = 3;
    int speedPinA = 6; //   เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์ 

// Motor B Right
    int dir1PinB = 4;
    int dir2PinB = 5;
    int speedPinB = 7; // เพื่อให้ PWM สามารถควบคุมความเร็วมอเตอร์

    
//Counter speed sensor-----------------------------------------------------------------------//
    const byte interruptPinL = 18;
    const byte interruptPinR = 19;
    
    long Left,Right;
    int normalSpeed = 192; // 25% Duty Cycle
  class PID{
public:
  double error;
  double sample;
  double lastSample;
  double kP, kI, kD;      
  double P, I, D;
  double pid;
  
  double setPoint;
  long lastProcess; 
  PID(double _kP, double _kI, double _kD){
    kP = _kP;
    kI = _kI;
    kD = _kD;
  }
  void addNewSample(double _sample){
    sample = _sample;
  } 
  void setSetPoint(double _setPoint){
    setPoint = _setPoint;
  } 
  double process(){
    // Implementação P ID
    error = setPoint - sample;
    float deltaTime = (millis() - lastProcess) / 1000.0;
    lastProcess = millis();
    //P
    P = error * kP;
    //I
    I = I + (error * kI) * deltaTime;
    
    //D
    D = (lastSample - sample) * kD / deltaTime;
    lastSample = sample;
    // Soma tudo
    pid = P + I + D;   
    return pid;
  }
};
PID pid(3, 7, 0.05);
void setup() {
  pid.setSetPoint(0.0);
   Serial.begin(9600);//set board
//interrupt--------------------------------------------------------------------
  pinMode(interruptPinL, INPUT);
  pinMode(interruptPinR, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), ISR_L, RISING );
  attachInterrupt(digitalPinToInterrupt(19), ISR_R, RISING  );
//Motor--------------------------------------------------------------------------
  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(speedPinB,OUTPUT);
}
void ISR_L(){
    Left++;
}
void ISR_R(){
    Right++; 
}    
void loop() {
  // TODO: critical section
  long error = Left - Right;
  long minCount = min(Left, Right);
  Left -= minCount;
  Right -= minCount;
  
  // Add new sample to PID
  pid.addNewSample(error);
  
  // PID feedback
  int powerDiff = int(pid.process());
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print(" | powerDiff: ");
  Serial.println(powerDiff);
  // Update motor speed
  if (powerDiff < 0)
    set_power(normalSpeed + powerDiff, normalSpeed);
  else
    set_power(normalSpeed, normalSpeed - powerDiff);
}

int set_power(int speed_left,int speed_right){
  
  speed_left = max(min(speed_left, 255), 0);
  speed_right = max(min(speed_right, 255), 0);
  
  // Motor A ด้านซ้าย
  analogWrite(speedPinA, speed_left); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);
  // Motor B ด้านขวา
  analogWrite(speedPinB, speed_right); //ตั้งค่าความเร็ว PWM ผ่านตัวแปร ค่าต่ำลง มอเตอร์จะหมุนช้าลง
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}

