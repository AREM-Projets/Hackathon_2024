#pragma once

#include "Constants.h"
#include "Tof.h"
#include "Motor.h"


class Base
{
public:
  void init();
  void run(rundir dir);
  bool proximity(unsigned int seuil = 140);
  void print_param(void);
  void run_m(rundir dir, float d);
  void turn_deg(side s, unsigned int a);

  Tof sensor;


private:
  Motor motorL;
  Motor motorR;
  
  // motors variables
  unsigned long motors_start_time;
  bool motors_on;

  // theorical position values
  float posx_th; //m
  float posy_th; //m
  float angle_th; //rad
};
