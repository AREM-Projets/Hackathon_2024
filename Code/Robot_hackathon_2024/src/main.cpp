/*
TOF sur D4: SDA; D5: SCL
*/

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

#define TOF_XSDN D3

#define MOTOR_G_BACKWARD_STOP 1475
#define MOTOR_G_FORWARD_STOP 1575
#define MOTOR_G_SPEED_RANGE 50

#define MOTOR_D_BACKWARD_STOP 1565
#define MOTOR_D_FORWARD_STOP 1465
#define MOTOR_D_SPEED_RANGE 50







typedef enum {LEFT, RIGHT} side;
typedef enum {FORWARD, BACKWARD, STOP} rundir;

/*Classes*/
class Motor
{
public:
  void motor_init(side s);
  void motor_run(rundir dir);
  


private:
  Servo motor_port;
  unsigned int motor_side;
  unsigned int motor_forward_stop;
  unsigned int motor_backward_stop;
  unsigned int motor_speed_range;
};


void Motor::motor_init(side s) {
  motor_side = s;

  if(s == LEFT) {
    motor_port.attach(A1);
    motor_backward_stop = MOTOR_G_BACKWARD_STOP;
    motor_forward_stop = MOTOR_G_FORWARD_STOP;
    motor_speed_range = MOTOR_G_SPEED_RANGE;
  }
  else if(s == RIGHT) {
    motor_port.attach(A0);
    motor_backward_stop = MOTOR_D_BACKWARD_STOP;
    motor_forward_stop = MOTOR_D_FORWARD_STOP;
    motor_speed_range = MOTOR_D_SPEED_RANGE;
  }
}

void Motor::motor_run(rundir dir) {
  if(dir == FORWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_forward_stop + motor_speed_range - 7);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_forward_stop - motor_speed_range);
  }

  else if(dir == BACKWARD) {
    if(motor_side == LEFT) motor_port.writeMicroseconds(motor_backward_stop - motor_speed_range);
    else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_backward_stop + motor_speed_range);
  }

  else if(dir == STOP) {
    motor_port.writeMicroseconds(motor_backward_stop);
  }
}



class Base
{
public:
  void base_init();
  void base_run(rundir dir);


private:
  Motor motorL;
  Motor motorR;
  VL53L1X sensor;
};


void Base::base_init() {
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




  motorL.motor_init(LEFT);
  motorR.motor_init(RIGHT);
}



void Base::base_run(rundir dir) {
  motorL.motor_run(dir);
  motorR.motor_run(dir);
}

// void init_tof(VL53L1X& sensor);

// prototypes des fonctions de navigation:
// void set_speed(float speed);
// void set_position(float posx);
// void set_angle(float angle);


Base robot;


void setup() {

  Serial.begin(9600);

  robot.base_init();
  robot.base_run(BACKWARD);
  
  

}


void loop()
{
  // Serial.print(sensor.read());

  // Serial.println();
}

