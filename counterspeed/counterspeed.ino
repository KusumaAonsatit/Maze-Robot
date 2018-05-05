int inputPin= 19;
int i;
void setup(){
pinMode(inputPin, INPUT);
}
void loop(){
int value= digitalRead(inputPin);
if (value == HIGH)
{
i++;
Serial.println(i);
}
}
