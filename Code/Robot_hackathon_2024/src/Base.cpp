#include "Base.h"
#include "Constants.h"
#include "Arduino.h"
#include <math.h>



void Base::init() {

  // sensor init
  sensor.init();

  // motors init
  motorL.init(LEFT);
  motorR.init(RIGHT);
  motors_on = false;

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
    motors_on = true;
    
    motorL.run(dir);
    motorR.run(dir);

    motors_start_time = millis();
  }
  else if(dir == STOP && motors_on){
    

    motorL.run(dir);
    motorR.run(dir);
    motors_on = false;

    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    posx_th += dist*cos(angle_th);
    posy_th += dist*sin(angle_th);


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


void Base::turn_deg(side s, unsigned int a) {
  float angle_rad = a* (3.14159)/180;
  if(s == LEFT) angle_th += angle_rad;
  else if(s == RIGHT) angle_th -= angle_rad; 

  if(s == LEFT) {
    motorL.run(BACKWARD);
    motorR.run(FORWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
    motorL.run(STOP);
    motorR.run(STOP);
  }
  else if(s == RIGHT) {
    motorL.run(FORWARD);
    motorR.run(BACKWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
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
  Serial.print(posx_th);
  Serial.println(" m");
  Serial.print("posy_th: ");
  Serial.print(posy_th);
  Serial.println(" m");
  Serial.print("Angle: ");
  Serial.print(angle_th * 180 / (3.14159));
  Serial.println(" °");

  Serial.println();
}


float Base::get_posx(void)
{
  if(motors_on)
  {
    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    posx_th += dist*cos(angle_th); //mise a jour de la position si on est en train de rouler
  }
  // si on est pas en train de rouler, cela veut dire qu'on a deja calcule la position lors du stop et on peut juste renvoyer la position
  return posx_th;
  
}


float Base::get_posy(void)
{
  if(motors_on)
  {
    // distance travelled calculation
    unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
    //Serial.println(t);
    float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
    // Serial.println(dist);


    posy_th += dist*sin(angle_th);
  }
  
  return posy_th;
  
}

float Base::get_angle(void)
{
  return angle_th;
}
