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


  robot.run(FORWARD);
  while(robot.get_posx() < 100);
  robot.turn_deg(LEFT, 90);
  robot.stop();
}


void loop()
{
  // robot.run(FORWARD);

  // while(!robot.proximity()) {
  //   robot.print_param();
  // }

  // robot.run(STOP);
  // while(robot.proximity()) {
  //   robot.turn_deg(LEFT, 30);
  // }

  
  // robot.print_param();
  
}

