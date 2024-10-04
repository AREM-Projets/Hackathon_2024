#include <Arduino.h>
#include <Servo.h>


Servo motorL;
Servo motorR;


void setup() {

  motorR.attach(A0);
  motorL.attach(A1);

  motorL.writeMicroseconds(2000);
  motorR.writeMicroseconds(1000);

}


void loop()
{
}


