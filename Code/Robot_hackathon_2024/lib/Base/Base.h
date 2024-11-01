#pragma once

#include "Constants.h"
#include "Tof.h"
#include "Motor.h"

float DegToRad(float a);
float RadToDeg(float a);


class Base
{
public:
  void init();
  void run(rundir dir);
  void stop(void);
  bool proximity(unsigned int seuil = 140); // a modifier
  void print_param(void);
  void run_m(rundir dir, float d); //a modifier
  void turn_rad(float angle_rad);
  float get_posx(void);
  float get_posy(void);
  float get_angle(void);

  rundir get_motors_status(void);

  Tof sensor;


private:
  Motor motorL;
  Motor motorR;
  
  // motors variables
  unsigned long motors_start_time;
  rundir motors_on;

  // theorical position values
  float posx_th; //m
  float posy_th; //m
  float angle_th; //rad
};
