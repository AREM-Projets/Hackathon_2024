/*
TOF sur D4: SDA; D5: SCL

Plage de vitesses moteur droit:
Marche avant: 85 - 89
Marche arrière: 101 - 105

Plage de vitesses moteur gauche:
Marche avant: 100 - 104
Marche arrière: 85 - 88
*/

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

#define TOF_XSDN D3
#define MOTOR_D_BACKWARD_STOP 1565
#define MOTOR_D_FORWARD_STOP 1465

#define MOTOR_G_BACKWARD_STOP 1475
#define MOTOR_G_FORWARD_STOP 1575
#define MOTOR_G_SPEED_RANGE 50

#define MOTOR_STOPf_TO_STOPb_RANGE 100




void init_base(Servo& motorL, Servo& motorR);

// prototypes des fonctions de navigation:
// void set_speed(float speed);
// void set_position(float posx);
// void set_angle(float angle);

Servo motorL;
Servo motorR;




void setup() {

  init_base(motorL, motorR);


 
  motorL.writeMicroseconds(MOTOR_G_FORWARD_STOP+MOTOR_G_SPEED_RANGE-7);
  motorR.writeMicroseconds(MOTOR_D_FORWARD_STOP-MOTOR_G_SPEED_RANGE);

}


void loop()
{



}



void init_base(Servo& motorL, Servo& motorR) {
  motorR.attach(A0);
  motorL.attach(A1);
}
