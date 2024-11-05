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

  void run(rundir_t dir);
  void run_m(double d);
  void turn_rad(double angle_rad);
  void stop(void);
  
  uint16_t getSensorDistance(void);

  void print_param(void);

  double get_posx(void);
  double get_posy(void);
  double get_angle(void);

  rundir_t get_motors_status(void);

  


private:
  Motor _motorL;
  Motor _motorR;
  Tof _sensor;
  
  // motors variables
  unsigned long _motors_start_time;
  rundir_t _motors_state;

  // theorical position values
  double _posx_th; //m
  double _posy_th; //m
  double _angle_th; //rad
};
