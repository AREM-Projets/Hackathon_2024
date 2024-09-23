#pragma once
#include "Constants.h"
#include "Servo.h"



/*Classes*/
class Motor
{
  /*Classe pour definir les methodes pour controller les moteurs à rotation continue du robot hackathon*/
public:
  void init(side s);
  void run(rundir dir);


private:
  Servo motor_port;
  unsigned int motor_side;
  unsigned int motor_forward_stop;
  unsigned int motor_backward_stop;
  unsigned int motor_speed_range;
};