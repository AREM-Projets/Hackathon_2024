/*
TOF sur D4: SDA; D5: SCL
*/

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <math.h>

#define TOF_XSDN D3

#define MOTOR_G_BACKWARD_STOP 1475
#define MOTOR_G_FORWARD_STOP 1575
#define MOTOR_G_SPEED_RANGE 50

#define MOTOR_D_BACKWARD_STOP 1565
#define MOTOR_D_FORWARD_STOP 1465
#define MOTOR_D_SPEED_RANGE 50

#define ROBOT_SPEED_MS 0.1174 //robot speed in m/s
#define ROBOT_WHEEL_SPACING_M 0.114 //robot space between wheels in m
#define ROBOT_ANGLUAR_SPEED_COEF 0.95 //angular speed correction coefficient

#define ROBOT_ANGULAR_SPEED_DEGS 2*ROBOT_SPEED_MS/ROBOT_WHEEL_SPACING_M * ROBOT_ANGLUAR_SPEED_COEF



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
















class Tof
{
public:
  void tof_init(void);
  bool tof_proximity(unsigned int seuil);
  void tof_print_measure(void);


private:
  VL53L1X sensor;
};


void Tof::tof_init(void) {
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


bool Tof::tof_proximity(unsigned int seuil) {
  if(sensor.read() < seuil) return true;
  else return false;
}

void Tof::tof_print_measure(void) {
  Serial.print("Proximity: ");
  Serial.print(sensor.read());
  Serial.println(" mm");
}















class Base
{
public:
  void base_init();
  void base_run(rundir dir);
  bool base_proximity(unsigned int seuil = 140);
  void base_print_param(void);
  void base_run_m(rundir dir, float d);
  void base_turn_deg(side s, unsigned int a);


private:
  Motor motorL;
  Motor motorR;
  Tof sensor;

  // theorical position values
  float posx_th;
  float posy_th;
  float angle_th;
};


void Base::base_init() {
  sensor.tof_init();
  motorL.motor_init(LEFT);
  motorR.motor_init(RIGHT);

  // positioning system initialisation
  posx_th = 0;
  posy_th = 0;
  angle_th =0;
}



void Base::base_run(rundir dir) {
  /*to be deleted*/
  motorL.motor_run(dir);
  motorR.motor_run(dir);
}



void Base::base_run_m(rundir dir, float d) {
  /*Warning: this method is blocking*/

  base_run(dir);
  delayMicroseconds(d/ROBOT_SPEED_MS*1000000);
  base_run(STOP);

  // update position
  posx_th += d*cos(angle_th);
  posy_th += d*sin(angle_th);

}


void Base::base_turn_deg(side s, unsigned int a) {
  float angle_rad = a* (3.14159)/180;
  if(s == LEFT) angle_th += angle_rad;
  else if(s == RIGHT) angle_th -= angle_rad; 

  if(s == LEFT) {
    motorL.motor_run(BACKWARD);
    motorR.motor_run(FORWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
    motorL.motor_run(STOP);
    motorR.motor_run(STOP);
  }
  else if(s == RIGHT) {
    motorL.motor_run(FORWARD);
    motorR.motor_run(BACKWARD);
    delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
    motorL.motor_run(STOP);
    motorR.motor_run(STOP);
  }
}




bool Base::base_proximity(unsigned int seuil) {
  return sensor.tof_proximity(seuil);
}



void Base::base_print_param(void) {
  sensor.tof_print_measure();
  Serial.print("posx_th: ");
  Serial.print(posx_th);
  Serial.println(" m");
  Serial.print("posy_th: ");
  Serial.print(posy_th);
  Serial.println(" m");
  Serial.print("Angle: ");
  Serial.print(angle_th * 180 / (3.14159));
  Serial.println(" °");
}













Base robot;


void setup() {

  Serial.begin(9600);
  Serial.println("Base start.");

  robot.base_init();

  // robot.base_run_m(FORWARD, 1);
  robot.base_turn_deg(RIGHT, 90);
  robot.base_run_m(FORWARD, 1);

  // robot.base_run(FORWARD);
  // while(!robot.base_proximity()) {
  //   robot.base_print_param();
  // }
  // robot.base_run(STOP);
}


void loop()
{
  robot.base_print_param();
}

