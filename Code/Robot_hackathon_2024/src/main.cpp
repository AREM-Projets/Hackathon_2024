/*
Code de demo du robot hackathon AREM 2024
Auteur: Antoine Chassaigne
Date: 11/2024
*/

#include "Arduino.h"
#include "Base.h" //bibliotheque qui contient les fonctions pour controller le robot


// On cree un objet robot. C'est un peu un jumeau virtuel du robot qui permet de le controller via des fonctions propres (methodes)
Base robot;

void setup() {
  // initialisation de la connexion usb
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("---Serial ready---");

  // initialisation de l'embase du robot (capteur tof et moteurs)
  robot.init();

  // initialisation du bouton équipe et des leds equipe
  pinMode(BOUTON_EQUIPE, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  /* Code utilisateur 0 */
  // Allumage LED equipe en fonction du bouton equipe
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
  /* Fin code utilisateur 0 */

  /* Code utilisateur 1 */

  // exemple de code
  // robot.run(FORWARD);
  // while(robot.getPosX() < 1)
  // {
  //   robot.printParams();
  // }
  // robot.stop();

  // robot.run(BACKWARD);
  // while(robot.getPosX() > 0)
  // {
  //   robot.printParams();
  // }

  robot.runDistance(1);
  robot.printParams();
  delay(1000);
  robot.runDistance(-robot.getPosX());
  robot.printParams();
  
  /* Fin code utilisateur 1 */
}


void loop()
{
  /* Code utilisateur 2 */



  // have fun !
  // N'oubliez pas, comme l'a dit un grand homme : "Y'a un fichier il s'appelle README je me demande pourquoi."

  /* Fin code utilisateur 2 */
}




