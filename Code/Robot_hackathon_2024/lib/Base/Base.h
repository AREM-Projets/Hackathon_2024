/*
TODO:
- fonctions de positionnement relatif (en premier)
- fonctions de positionnement absolu (en second)
*/


#pragma once

#include "Constants.h"
#include "Tof.h"
#include "Motor.h"

#define SPEED_INC 100


class Base
{
public:
  void init();

  void run_speed(int left_speed, int right_speed);

  void run(rundir_t dir);
  void turn(side_t s);
  void runDistance(double dist_m);
  void turnAngle(double angle_rad);
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
