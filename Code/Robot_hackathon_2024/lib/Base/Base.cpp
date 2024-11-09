#include "Base.h"
#include "Constants.h"
#include "Arduino.h"
#include <math.h>

/**
 * @brief Initialise 
 * 
 */
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
  _angle_th = 0;
}


/**
 * @brief Fait rouler le robot dans une direction donnée
 * 
 * @param dir direction du mouvement (FORWARD / BACKWARD)
 */
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

/**
 * @brief Arrête le robot.
 * 
 */
void Base::stop(void)
{
  this->run(STOP);
}

/**
 * @brief Fait rouler le robot d'une distance en metres donnee
 * Attention : fonction bloquante.
 * 
 * @param dist_m distance en m (distance négative pour reculer)
 */
void Base::runDistance(double dist_m) {
  if(dist_m > 0) this->run(FORWARD);
  else this->run(BACKWARD);

  delayMicroseconds(fabs(dist_m/(ROBOT_SPEED_MS)*1000000));

  this->run(STOP);
}

/**
 * @brief tourne d'un angle donné en rad . 
 * Attention : fonction bloquante.
 * 
 * @param angle_rad angle en rad (ou angle en degré * DEG_TO_RAD)
 */
void Base::turn(double angle_rad) {
  side_t s;

  _angle_th -= angle_rad;

  // Keep angle between -180 and 180°
  if (_angle_th > 180*DEG_TO_RAD)
  {
    _angle_th -= 360*DEG_TO_RAD;
  }
  else if (_angle_th <= -180*DEG_TO_RAD)
  {
    _angle_th += 360*DEG_TO_RAD;
  }
  
  

  if(angle_rad > 0) s = LEFT;
  else s = RIGHT;

  if(s == LEFT) {
    _motorL.run(BACKWARD);
    _motorR.run(FORWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    _motorL.run(STOP);
    _motorR.run(STOP);
  }
  else if(s == RIGHT) {
    _motorL.run(FORWARD);
    _motorR.run(BACKWARD);
    delayMicroseconds(-angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    _motorL.run(STOP);
    _motorR.run(STOP);
  }
}

/**
 * @brief Renvoie la distance détectée par le capteur (en mm)
 * 
 * @return uint16_t : distance en mm
 */
uint16_t Base::getSensorDistance(void) {
  /*Encapsulation de la methode de proximite de la classe Tof*/
  return _sensor.getDistance();
}


void Base::printParams(void) {
  _sensor.printDistance();
  Serial.print("X : ");
  Serial.print(getPosX());
  Serial.println(" m");
  Serial.print("Y : ");
  Serial.print(getPosY());
  Serial.println(" m");
  Serial.print("Angle : ");
  Serial.print(getAngle() * RAD_TO_DEG);
  Serial.println(" °");

  Serial.println();
}


double Base::getPosX(void)
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


double Base::getPosY(void)
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

double Base::getAngle(void)
{
  return _angle_th;
}


rundir_t Base::getMotorsStatus(void)
{
  return _motors_state;
}