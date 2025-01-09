/*
Code de demo du robot hackathon AREM 2024
Auteur: Antoine Chassaigne
Date: 11/2024
*/

#include "Arduino.h"
#include "Base.h" //bibliotheque qui contient les fonctions pour controller le robot

HardwareSerial Serial1(PA10, PA9); // uart telecommande
Base robot;
char recval;

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
      robot.stop();
      break;

    case 'u':
      // avancer
      robot.run(FORWARD);
      break;

    case 'd':
      // reculer
      robot.run(BACKWARD);
      break;

    case 'l':
      // tourner a gauche
      robot.turn(15*DEG_TO_RAD);
      break;

    case 'r':
      // tourner a droite
      robot.turn(-15*DEG_TO_RAD);
      break;
    
    default:
      break;
    }

  }
  
}




