#include <Wire.h>
int ledPinl = 22;
int ledPinf = 24;
int ledPinr = 26;

boolean bLedOn = true;

void setup() {
  pinMode(ledPinl, OUTPUT);
  pinMode(ledPinf, OUTPUT);
  pinMode(ledPinr, OUTPUT);

}

void loop() {
  digitalWrite(ledPinl, bLedOn);
  digitalWrite(ledPinf, bLedOn);
  digitalWrite(ledPinr, bLedOn);
  bLedOn = !bLedOn;
  delay(1000);
}
