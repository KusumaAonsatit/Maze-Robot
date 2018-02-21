#include <HMC5983.h>
#include <Wire.h>

HMC5983 compass;

void setup () {
  Serial.begin(9600);
  compass.begin(); // use "true" if you need some debug information
}

void loop() {
  float c ;
  c = compass.read();
  
    Serial.println(c);
    delay(500);
}
