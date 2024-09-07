/*
TOF sur D4: SDA; D5: SCL

Plage de vitesses moteur droit:
Marche avant: 85 - 89
Marche arrière: 101 - 105

Plage de vitesses moteur gauche:
Marche avant: 100 - 104
Marche arrière: 85 - 88
*/

#include <Arduino.h>
#include <Servo.h>


#include <Wire.h>
#include <VL53L1X.h>

#define TOF_XSDN D3
#define STOP_HAUT 100
#define STOP_BAS 90
#define SPEED_RANGE 5


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

  moteurD.attach(A0); //A1
  moteurG.attach(A1); //A0

  moteurD.write(86);
  moteurG.write(103);

}


void loop()
{
  Serial.print(sensor.read());

  Serial.println();





  // // Code pour tester les plages de vitesses
  // for(int i=STOP_BAS-SPEED_RANGE; i<= STOP_HAUT+SPEED_RANGE; i++) {
  //   moteurD.write(i);
  //   Serial.println(i);
  //   delay(1000);
  // }
  
  // for(int i=STOP_HAUT+SPEED_RANGE; i>= STOP_BAS-SPEED_RANGE; i--) {
  //   moteurD.write(i);
  //   Serial.println(i);
  //   delay(1000);
  // }

}