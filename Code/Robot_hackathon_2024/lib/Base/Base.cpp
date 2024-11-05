#include "Base.h"
#include "Constants.h"
#include "Arduino.h"
#include <math.h>



void Base::init() {

  // sensor init
  _sensor.init();

  // motors init
  _motorL.init(LEFT);
  _motorR.init(RIGHT);
  _motors_state = STOP;

  // positioning system initialisation
  _posx_th = 0;
  _posy_th = 0;
  _angle_th =0;
}



void Base::run(rundir_t dir) {
  /*Fait rouler en ligne droite le robot dans le sens (avant / arriere) voulu.
  Permet aussi d'arreter le robot via STOP. Cette fonction, comme les autres fonctions de deplacement,
  Met a jour la position theorique du robot (duree de deplacement * vitesse)*/

  if(dir != STOP && _motors_state == STOP) {
    _motors_state = dir;
    
    _motorL.run(dir);
    _motorR.run(dir);

    _motors_start_time = millis();
  }
  else if(dir == STOP && _motors_state != STOP){
    

    _motorL.run(dir);
    _motorR.run(dir);
    

    // distance travelled calculation
    unsigned long t = (millis() - _motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    double dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);

    // update pos
    if(_motors_state == FORWARD) 
    {
      _posx_th += dist*cos(_angle_th);
      _posy_th += dist*sin(_angle_th);
    }
    if(_motors_state == BACKWARD)
    {
      _posx_th -= dist*cos(_angle_th);
      _posy_th -= dist*sin(_angle_th);
    }

    _motors_state = STOP;
  }
}


void Base::stop(void)
{
  run(STOP);
}


void Base::run_m(double d) {
  /*Fait avancer le robot d'une distance en metres donnee*/
  /*Warning: this method is blocking*/
  if(d > 0) run(FORWARD);
  else run(BACKWARD);

  delayMicroseconds(d/ROBOT_SPEED_MS*1000000);

  run(STOP);

  // update position
  _posx_th += d*cos(_angle_th);
  _posy_th += d*sin(_angle_th);

}


void Base::turn_rad(double angle_rad) {
  side_t s;

  
  _angle_th += angle_rad;


  if(angle_rad > 0) s = RIGHT;
  else s = LEFT;


  if(s == LEFT) {
    _motorL.run(BACKWARD);
    _motorR.run(FORWARD);
    delayMicroseconds(-angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    _motorL.run(STOP);
    _motorR.run(STOP);
  }
  else if(s == RIGHT) {
    _motorL.run(FORWARD);
    _motorR.run(BACKWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    _motorL.run(STOP);
    _motorR.run(STOP);
  }
}




uint16_t Base::getSensorDistance(void) {
  /*Encapsulation de la methode de proximite de la classe Tof*/
  return _sensor.getDistance();
}



void Base::print_param(void) {
  Serial.printf("Sensor distance: %d\n", _sensor.getDistance());
  Serial.print("posx_th: ");
  Serial.print(get_posx());
  Serial.println(" m");
  Serial.print("posy_th: ");
  Serial.print(get_posy());
  Serial.println(" m");
  Serial.print("Angle: ");
  Serial.print(get_angle() * RAD_TO_DEG);
  Serial.println(" °");

  Serial.println();
}


double Base::get_posx(void)
{
  double dist = 0;


  if(_motors_state != STOP)
  {
    // distance travelled calculation
    unsigned long t = (millis() - _motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


  }
  // we do not update de position as we are still running
  if(_motors_state == FORWARD) return _posx_th + dist*cos(_angle_th);
  else if(_motors_state == BACKWARD) return _posx_th - dist*cos(_angle_th);
  else return _posx_th;
}


double Base::get_posy(void)
{
  double dist = 0;

  if(_motors_state != STOP)
  {
    // distance travelled calculation
    unsigned long t = (millis() - _motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);
    // Serial.println();
    // Serial.println(posy_th + dist*sin(angle_th));

  }
  // we do not update de position as we are still running
  if(_motors_state == FORWARD) return _posy_th + dist*sin(_angle_th);
  else if(_motors_state == BACKWARD) return _posy_th - dist*sin(_angle_th);
  else return _posy_th;
}

double Base::get_angle(void)
{
  return _angle_th;
}




rundir_t Base::get_motors_status(void)
{
  return _motors_state;
}