#include "Motor.h"
#include "Arduino.h"
#include "Constants.h"


void Motor::init(side s) {
  /*Initialise le moteur a rotation continue en fonction de son cote sur le chassis*/
  motor_side = s;

  if(s == LEFT) {
    motor_port.attach(A1);
    motor_stop = MOTOR_G_STOP;
    motor_speed_range = MOTOR_G_SPEED_RANGE;
  }
  else if(s == RIGHT) {
    motor_port.attach(A0);
    motor_stop = MOTOR_D_STOP; 
    motor_speed_range = MOTOR_D_SPEED_RANGE;
  }
}

void Motor::run(rundir dir) {
  /*Fait tourner le moteur dans la direction souhaitee en fonction du cote du moteur sur le chassis de manière infinie*/
  
  
  if(dir == FORWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_stop + motor_speed_range*ROBOT_L_MOTOR_COEF*ROBOT_SPEED_COEF);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_stop - motor_speed_range*ROBOT_R_MOTOR_COEF*ROBOT_SPEED_COEF);
  }

  else if(dir == BACKWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_stop - motor_speed_range*ROBOT_L_MOTOR_COEF*ROBOT_SPEED_COEF);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_stop + motor_speed_range*ROBOT_R_MOTOR_COEF*ROBOT_SPEED_COEF);
  }

  else if(dir == STOP) {
    motor_port.writeMicroseconds(motor_stop);
  }
}

