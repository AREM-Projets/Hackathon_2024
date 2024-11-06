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
  void runDistance(double dist_m);
  void turn(double angle_rad);
  void stop(void);
  
  uint16_t getSensorDistance(void);

  void printParams(void);

  double getPosX(void);
  double getPosY(void);
  double getAngle(void);

  rundir_t getMotorsStatus(void);

  


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
