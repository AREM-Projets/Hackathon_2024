/*
TOF sur D4: SDA; D5: SCL
*/


#include "Base.h"
#include "Arduino.h"





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
}


void loop()
{
  robot.run(FORWARD);

  while(!robot.proximity()) {
    robot.print_param();
  }

  robot.run(STOP);
  delay(500);
  robot.run(BACKWARD);
  delay(200);
  robot.stop();
  while(robot.proximity()) {
    robot.turn_deg(LEFT, 20);
  }

  
  robot.print_param();
  
}

