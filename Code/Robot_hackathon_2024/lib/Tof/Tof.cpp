#include "Tof.h"
#include "Constants.h"
#include "Arduino.h"
#include <Wire.h>



void Tof::init(void) {
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  sensor.startContinuous(200);
}


bool Tof::proximity(void) {
  /*Renvoie la distance d'un objet avec le robot*/
  return sensor.read();
}

void Tof::print_measure(void) {
  /**/
  Serial.print("Proximity: ");
  Serial.print(sensor.read());
  Serial.println(" mm");
}
