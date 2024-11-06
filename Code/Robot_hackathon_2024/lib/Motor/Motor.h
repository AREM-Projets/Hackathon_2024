#pragma once
#include "Constants.h"
#include "Servo.h"



/*Classes*/
class Motor
{
  /*Classe pour definir les methodes pour controller les moteurs à rotation continue du robot hackathon*/
public:
  void init(side_t side);
  void run(rundir_t dir);


private:
  Servo _motor_port;
  side_t _motor_side;
  uint32_t _motor_stop;
  uint32_t _motor_speed_range;
};