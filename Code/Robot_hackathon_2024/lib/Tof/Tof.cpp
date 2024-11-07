#include "Tof.h"
#include "Constants.h"
#include "Arduino.h"
#include <Wire.h>



void Tof::init(void) {
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  _sensor.setTimeout(500);
  if (!_sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  _sensor.setDistanceMode(VL53L1X::Long);
  _sensor.setMeasurementTimingBudget(50000);

  // Start continuous readings at a rate of one measurement every 50 ms (the
  // inter-measurement period). This period should be at least as long as the
  // timing budget.
  _sensor.startContinuous(SENSOR_POOL_PERIOD_MS);
}

void Tof::printDistance(void)
{
  Serial.printf("Sensor distance : %d\n", this->getDistance());
}

uint16_t Tof::getDistance(void) {
  /*Renvoie la distance d'un objet avec le robot*/
  return _sensor.read();
}
