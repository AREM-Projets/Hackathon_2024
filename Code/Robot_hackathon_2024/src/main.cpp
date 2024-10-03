/*
TOF sur D4: SDA; D5: SCL
*/


#include "Base.h"
#include "Arduino.h"





Base robot;


void setup() {

  while (!Serial) {}
  Serial.begin(9600); // a mettre la ou il y a des Serial.print dans les classes


  robot.init();

  //test de roulage en distance
  // robot.run(FORWARD);
  // while(robot.get_posx() < 100);
  // robot.turn_deg(LEFT, 90);
  // robot.stop();
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

