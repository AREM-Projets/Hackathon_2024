/*
Code de demo du robot hackathon AREM 2024
Auteur: Antoine Chassaigne
Date: 11/2024
*/


#include "Arduino.h"
#include "Base.h" //bibliotheque qui contient les fonctions pour controller le robot
#include "RobotsConfig.h"

HardwareSerial Serial1(PA10, PA9); // uart telecommande
Base robot;
char recval;
int lspeed = 0;
int rspeed = 0;

void setup() {


  Serial.begin(9600);
  Serial1.begin(115200);

  while (!Serial) {}
  Serial.println("---Serial ready---");

  robot.init();

  pinMode(BOUTON_EQUIPE, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  
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

}


void loop()
{
  while (Serial1.available()) {
    recval = Serial1.read(); // recuperation caractere uart
    Serial.print("Message reçu : ");
    Serial.println(recval);
    

    switch (recval)
    {
    case 'c':
      // stop
      // robot.stop();
      lspeed = 0;
      rspeed = 0;
      break;

    case 'u':
      // avancer
      // robot.stop();
      // robot.run(FORWARD);      
      lspeed = SPEED_INC*LINEAR_SPEED;
      rspeed = SPEED_INC*LINEAR_SPEED;
    
      
      break;

    case 'd':
      // reculer
      // robot.stop();
      // robot.run(BACKWARD);
      lspeed = -SPEED_INC*LINEAR_SPEED;
      rspeed = -SPEED_INC*LINEAR_SPEED;
      break;

    case 'l':
      // tourner a gauche
      // robot.stop();
      // robot.turn(LEFT);
      if(lspeed == rspeed) {
        // si on est pas en train de tourner
        lspeed -= SPEED_INC*ROTATION_SPEED;
        rspeed += SPEED_INC*ROTATION_SPEED;
      }
      break;

    case 'r':
      // tourner a droite
      // robot.stop();
      // robot.turn(RIGHT);
      if(lspeed == rspeed) {
        // si on est pas en train de tourner
        lspeed += SPEED_INC*ROTATION_SPEED;
        rspeed -= SPEED_INC*ROTATION_SPEED;
      }
      break;
    
    default:
      break;
    }

    robot.run_speed(lspeed, rspeed);

  }
  
}




