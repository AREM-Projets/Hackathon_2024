#include "Motor.h"
#include "Arduino.h"
#include "Constants.h"


void Motor::init(side s) {
  /*Initialise le moteur a rotation continue en fonction de son cote sur le chassis*/
  motor_side = s;

  if(s == LEFT) {
    motor_port.attach(A1);
    motor_backward_stop = MOTOR_G_BACKWARD_STOP;
    motor_forward_stop = MOTOR_G_FORWARD_STOP;
    motor_speed_range = MOTOR_G_SPEED_RANGE;
  }
  else if(s == RIGHT) {
    motor_port.attach(A0);
    motor_backward_stop = MOTOR_D_BACKWARD_STOP;
    motor_forward_stop = MOTOR_D_FORWARD_STOP;
    motor_speed_range = MOTOR_D_SPEED_RANGE;
  }
}

void Motor::run(rundir dir) {
  /*Fait tourner le moteur dans la direction souhaitee en fonction du cote du moteur sur le chassis de manière infinie*/
  if(dir == FORWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_forward_stop + motor_speed_range - 7);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_forward_stop - motor_speed_range);
  }

  else if(dir == BACKWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_backward_stop - motor_speed_range);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_backward_stop + motor_speed_range);
  }

  else if(dir == STOP) {
    motor_port.writeMicroseconds(motor_backward_stop);
  }
}

