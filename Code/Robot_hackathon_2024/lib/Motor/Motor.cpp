#include "Motor.h"
#include "Arduino.h"
#include "Constants.h"


void Motor::init(side_t side) {
  /*Initialise le moteur a rotation continue en fonction de son cote sur le chassis*/
  _motor_side = side;

  if(side == LEFT) {
    _motor_port.attach(A1);
    _motor_stop = MOTOR_G_STOP;
    _motor_speed_range = MOTOR_G_SPEED_RANGE;
  }
  else if(side == RIGHT) {
    _motor_port.attach(A0);
    _motor_stop = MOTOR_D_STOP; 
    _motor_speed_range = MOTOR_D_SPEED_RANGE;
  }
}

void Motor::run(rundir_t dir) {
  /*Fait tourner le moteur dans la direction souhaitee en fonction du cote du moteur sur le chassis de manière infinie*/
  
  switch (dir)
  {
  case FORWARD:
    if(_motor_side == LEFT) 
      _motor_port.writeMicroseconds(_motor_stop + _motor_speed_range*ROBOT_L_MOTOR_COEF*ROBOT_SPEED_COEF);
    else if(_motor_side == RIGHT) 
      _motor_port.writeMicroseconds(_motor_stop - _motor_speed_range*ROBOT_R_MOTOR_COEF*ROBOT_SPEED_COEF);
    break;

  case BACKWARD:
    if(_motor_side == LEFT) 
      _motor_port.writeMicroseconds(_motor_stop - _motor_speed_range*ROBOT_L_MOTOR_COEF*ROBOT_SPEED_COEF);
    else if(_motor_side == RIGHT)
      _motor_port.writeMicroseconds(_motor_stop + _motor_speed_range*ROBOT_R_MOTOR_COEF*ROBOT_SPEED_COEF);
    break;

  case STOP:
    _motor_port.writeMicroseconds(_motor_stop);
    break;
  
  default:
    break;
  }
}

