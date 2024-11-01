#include "Base.h"
#include "Constants.h"
#include "Arduino.h"
#include <math.h>



float DegToRad(float a)
{
  return(a * PI / 180);
}

float RadToDeg(float a)
{
  return(a * 180 / PI);
}


void Base::init() {

  // sensor init
  sensor.init();

  // motors init
  motorL.init(LEFT);
  motorR.init(RIGHT);
  motors_on = STOP;

  // positioning system initialisation
  posx_th = 0;
  posy_th = 0;
  angle_th =0;
}



void Base::run(rundir dir) {
  /*Fait rouler en ligne droite le robot dans le sens (avant / arriere) voulu.
  Permet aussi d'arreter le robot via STOP. Cette fonction, comme les autres fonctions de deplacement,
  Met a jour la position theorique du robot (duree de deplacement * vitesse)*/

  if(dir != STOP) {
    motors_on = dir;
    
    motorL.run(dir);
    motorR.run(dir);

    motors_start_time = millis();
  }
  else if(dir == STOP && motors_on != STOP){
    

    motorL.run(dir);
    motorR.run(dir);
    

    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    if(motors_on == FORWARD) 
    {
      posx_th += dist*cos(angle_th);
      posy_th += dist*sin(angle_th);
    }
    if(motors_on == BACKWARD)
    {
      posx_th -= dist*cos(angle_th);
      posy_th -= dist*sin(angle_th);
    }

    motors_on = STOP;
  }
}


void Base::stop(void)
{
  run(STOP);
}


void Base::run_m(rundir dir, float d) {
  /*Fait avancer le robot d'une distance en metres donnee*/
  /*Warning: this method is blocking*/

  run(dir);
  delayMicroseconds(d/ROBOT_SPEED_MS*1000000);
  run(STOP);

  // update position
  posx_th += d*cos(angle_th);
  posy_th += d*sin(angle_th);

}


void Base::turn_rad(float angle_rad) {
  side s;


  
  angle_th += angle_rad;


  if(angle_rad > 0) s = RIGHT;
  else s = LEFT;


  if(s == LEFT) {
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
    delayMicroseconds(-angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    motorL.run(STOP);
    motorR.run(STOP);
  }
  else if(s == RIGHT) {
    motorL.run(FORWARD);
    motorR.run(BACKWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_RADS*1000000);
    motorL.run(STOP);
    motorR.run(STOP);
  }
}




bool Base::proximity(unsigned int seuil) {
  /*Encapsulation de la methode de proximite de la classe Tof*/
  return sensor.proximity(seuil);
}



void Base::print_param(void) {
  sensor.print_measure();
  Serial.print("posx_th: ");
  Serial.print(get_posx());
  Serial.println(" m");
  Serial.print("posy_th: ");
  Serial.print(get_posy());
  Serial.println(" m");
  Serial.print("Angle: ");
  Serial.print(get_angle() * 180 / (3.14159));
  Serial.println(" °");

  Serial.println();
}


float Base::get_posx(void)
{
  float dist = 0;


  if(motors_on != STOP)
  {
    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    // posx_th += dist*cos(angle_th); //mise a jour de la position si on est en train de rouler
  }
  // si on est pas en train de rouler, cela veut dire qu'on a deja calcule la position lors du stop et on peut juste renvoyer la position
  
  if(motors_on == FORWARD) return posx_th + dist*cos(angle_th);
  else if(motors_on == BACKWARD) return posx_th - dist*cos(angle_th);
  else return posx_th;

}


float Base::get_posy(void)
{
  float dist = 0;

  if(motors_on != STOP)
  {
    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    // posy_th += dist*sin(angle_th);
  }
  
  if(motors_on == FORWARD) return posy_th + dist*sin(angle_th);
  else if(motors_on == BACKWARD) return posy_th - dist*sin(angle_th);
  else return posy_th;
}

float Base::get_angle(void)
{
  return angle_th;
}




rundir Base::get_motors_status(void)
{
  return motors_on;
}