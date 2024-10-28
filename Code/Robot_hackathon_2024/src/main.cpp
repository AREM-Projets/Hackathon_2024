/*
TOF sur D4: SDA; D5: SCL
*/


#include "Base.h"
#include "Arduino.h"


float DegToRad(float a)
{
  return(a * PI / 180);
}

float RadToDeg(float a)
{
  return(a * 180 / PI);
}


Base robot;


void setup() {

  // initialisation du bouton équipe et des leds
  pinMode(BOUTON_EQUIPE, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);


  // initialisation de la connexion usb
  while (!Serial) {}
  Serial.begin(9600);

  

  
  

  // Allumage LED equipe
  if(digitalRead(BOUTON_EQUIPE))
  {
    digitalWrite(LED1, 1);
    digitalWrite(LED2, 0);
  }
  else
  {
    digitalWrite(LED1, 0); 
    digitalWrite(LED2, 1);
  }
  
  robot.init();


  // robot.run(FORWARD);

  // while(robot.get_posx() < 1) {
  //   robot.print_param();
  // }

  // robot.run(STOP);

  // delay(1000);

  robot.run(BACKWARD);


  while(robot.get_posx() > -1) {
    robot.print_param();
  }

  robot.stop();


  // robot.turn_rad(DegToRad(180.0));
}


void loop()
{
  // robot.run(FORWARD);

  // while(!robot.proximity()) {
  //   robot.print_param();
  // }

  // robot.run(STOP);
  // delay(500);
  // robot.run(BACKWARD);
  // delay(500);
  // robot.stop();
  // while(robot.proximity()) {
  //   robot.turn_rad(DegToRad(20.0));
  // }
  
  // robot.print_param();
}

