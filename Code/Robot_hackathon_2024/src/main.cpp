/*
Code de demo du robot hackathon AREM 2024
Auteur: Antoine Chassaigne
Date: 11/2024
*/

#define SPEED_INC 220

#include "Arduino.h"
#include "Base.h" //bibliotheque qui contient les fonctions pour controller le robot

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

      // petit algo pour se remettre a avancer tout droit quand on appuie sur avancer en etant en rotation
      if(lspeed > rspeed) rspeed = lspeed;
      else if(rspeed > lspeed) lspeed = rspeed;
      else {
        lspeed += SPEED_INC;
        rspeed += SPEED_INC;
      }
      
      break;

    case 'd':
      // reculer
      // robot.stop();
      // robot.run(BACKWARD);
      lspeed -= SPEED_INC;
      rspeed -= SPEED_INC;
      break;

    case 'l':
      // tourner a gauche
      // robot.stop();
      // robot.turn(LEFT);
      lspeed -= SPEED_INC;
      rspeed += SPEED_INC;
      break;

    case 'r':
      // tourner a droite
      // robot.stop();
      // robot.turn(RIGHT);
      lspeed += SPEED_INC;
      rspeed -= SPEED_INC;
      break;
    
    default:
      break;
    }

    robot.run_speed(lspeed, rspeed);

  }
  
}




