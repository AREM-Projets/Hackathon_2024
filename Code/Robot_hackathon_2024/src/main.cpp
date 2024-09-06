#include <Arduino.h>
#include <Servo.h>

Servo moteurG;
Servo moteurD;

void setup() {
  
  moteurD.attach(A5);
  moteurG.attach(A6);

  moteurD.write(150);
  moteurG.write(50);

}

void loop() {
}
