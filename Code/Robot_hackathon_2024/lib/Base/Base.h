/*
TODO:
- fonctions de positionnement relatif (en premier)
- fonctions de positionnement absolu (en second)
*/


#pragma once

#include "Constants.h"
#include "Tof.h"
#include "Motor.h"



class Base
{
public:
  void init();

  void run(rundir dir);
  void run_m(double d);
  void turn_rad(double angle_rad);
  void stop(void);
  
  bool proximity(void);

  void print_param(void);

  double get_posx(void);
  double get_posy(void);
  double get_angle(void);

  rundir get_motors_status(void);

  


private:
  Motor motorL;
  Motor motorR;
  Tof sensor;
  
  // motors variables
  unsigned long motors_start_time;
  rundir motors_on;

  // theorical position values
  double posx_th; //m
  double posy_th; //m
  double angle_th; //rad
};
