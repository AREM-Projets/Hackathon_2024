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
#define MOTOR_D_BACKWARD_STOP 1565
#define MOTOR_D_FORWARD_STOP 1465

#define MOTOR_G_BACKWARD_STOP 1475
#define MOTOR_G_FORWARD_STOP 1575
#define MOTOR_G_SPEED_RANGE 50

#define MOTOR_STOPf_TO_STOPb_RANGE 100




void init_tof(VL53L1X& sensor);
void init_base(Servo& motorL, Servo& motorR);

// prototypes des fonctions de navigation:
// void set_speed(float speed);
// void set_position(float posx);
// void set_angle(float angle);

VL53L1X sensor;
Servo motorL;
Servo motorR;




void setup() {

  init_base(motorL, motorR);
  init_tof(sensor);


 
  motorL.writeMicroseconds(MOTOR_G_FORWARD_STOP+MOTOR_G_SPEED_RANGE-7);
  motorR.writeMicroseconds(MOTOR_D_FORWARD_STOP-MOTOR_G_SPEED_RANGE);

}


void loop()
{
  Serial.print(sensor.read());

  Serial.println();


}









void init_base(Servo& motorL, Servo& motorR) {
  motorR.attach(A0);
  motorL.attach(A1);
}

void init_tof(VL53L1X& sensor) {
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

}