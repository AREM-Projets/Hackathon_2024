/*
TOF sur D4: SDA; D5: SCL
*/

#include <Arduino.h>
#include <Servo.h>


#include <Wire.h>
#include <VL53L1X.h>

#define TOF_XSDN D3


VL53L1X sensor;


Servo moteurG;
Servo moteurD;
Servo head;

void setup() {

  


  pinMode(TOF_XSDN, OUTPUT);
  digitalWrite(TOF_XSDN, 0);
  pinMode(TOF_XSDN, INPUT);
  
  
  while (!Serial) {}
  Serial.begin(9600);
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

  // head.attach(A1);
  moteurD.attach(A1); //A2
  moteurG.attach(A0); //A0

  moteurD.write(150);
  moteurG.write(50);
  // head.write(50);

}


void loop()
{
  Serial.print(sensor.read());

  Serial.println();
}