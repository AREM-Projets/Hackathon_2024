/*
TOF sur D4: SDA; D5: SCL
*/

// #include <Arduino.h>
// #include <Servo.h>
// #include <Wire.h>
// #include <VL53L1X.h>
// #include <math.h>

// #define TOF_XSDN D3

// #define MOTOR_G_BACKWARD_STOP 1475
// #define MOTOR_G_FORWARD_STOP 1575
// #define MOTOR_G_SPEED_RANGE 50

// #define MOTOR_D_BACKWARD_STOP 1565
// #define MOTOR_D_FORWARD_STOP 1465
// #define MOTOR_D_SPEED_RANGE 50

// #define ROBOT_SPEED_MS 0.1174 //robot speed in m/s
// #define ROBOT_WHEEL_SPACING_M 0.114 //robot space between wheels in m
// #define ROBOT_ANGLUAR_SPEED_COEF 0.95 //angular speed correction coefficient

// #define ROBOT_ANGULAR_SPEED_DEGS 2*ROBOT_SPEED_MS/ROBOT_WHEEL_SPACING_M * ROBOT_ANGLUAR_SPEED_COEF



// typedef enum {LEFT, RIGHT} side;
// typedef enum {FORWARD, BACKWARD, STOP} rundir;
















// /*Classes*/
// class Motor
// {
// public:
//   void init(side s);
//   void run(rundir dir);


// private:
//   Servo motor_port;
//   unsigned int motor_side;
//   unsigned int motor_forward_stop;
//   unsigned int motor_backward_stop;
//   unsigned int motor_speed_range;
// };


// void Motor::init(side s) {
//   motor_side = s;

//   if(s == LEFT) {
//     motor_port.attach(A1);
//     motor_backward_stop = MOTOR_G_BACKWARD_STOP;
//     motor_forward_stop = MOTOR_G_FORWARD_STOP;
//     motor_speed_range = MOTOR_G_SPEED_RANGE;
//   }
//   else if(s == RIGHT) {
//     motor_port.attach(A0);
//     motor_backward_stop = MOTOR_D_BACKWARD_STOP;
//     motor_forward_stop = MOTOR_D_FORWARD_STOP;
//     motor_speed_range = MOTOR_D_SPEED_RANGE;
//   }
// }

// void Motor::run(rundir dir) {
//   if(dir == FORWARD) {
//     if(motor_side == LEFT) motor_port.writeMicroseconds(motor_forward_stop + motor_speed_range - 7);
//     else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_forward_stop - motor_speed_range);
//   }

//   else if(dir == BACKWARD) {
//     if(motor_side == LEFT) motor_port.writeMicroseconds(motor_backward_stop - motor_speed_range);
//     else if(motor_side == RIGHT) motor_port.writeMicroseconds(motor_backward_stop + motor_speed_range);
//   }

//   else if(dir == STOP) {
//     motor_port.writeMicroseconds(motor_backward_stop);
//   }
// }
















// class Tof
// {
// public:
//   void init(void);
//   bool proximity(unsigned int seuil);
//   void print_measure(void);


// private:
//   VL53L1X sensor;
// };


// void Tof::init(void) {
//   pinMode(TOF_XSDN, OUTPUT);
//   digitalWrite(TOF_XSDN, 0);
//   pinMode(TOF_XSDN, INPUT);
  
  
  
//   Wire.begin();
//   Wire.setClock(400000); // use 400 kHz I2C

//   sensor.setTimeout(500);
//   if (!sensor.init())
//   {
//     Serial.println("Failed to detect and initialize sensor!");
//     while (1);
//   }

//   sensor.setDistanceMode(VL53L1X::Long);
//   sensor.setMeasurementTimingBudget(50000);

//   // Start continuous readings at a rate of one measurement every 50 ms (the
//   // inter-measurement period). This period should be at least as long as the
//   // timing budget.
//   sensor.startContinuous(200);
// }


// bool Tof::proximity(unsigned int seuil) {
//   if(sensor.read() < seuil) return true;
//   else return false;
// }

// void Tof::print_measure(void) {
//   Serial.print("Proximity: ");
//   Serial.print(sensor.read());
//   Serial.println(" mm");
// }















// class Base
// {
// public:
//   void init();
//   void run(rundir dir);
//   bool proximity(unsigned int seuil = 140);
//   void print_param(void);
//   void run_m(rundir dir, float d);
//   void turn_deg(side s, unsigned int a);

//   Tof sensor;


// private:
//   Motor motorL;
//   Motor motorR;
  
//   // motors variables
//   unsigned long motors_start_time;
//   bool motors_on;

//   // theorical position values
//   float posx_th; //m
//   float posy_th; //m
//   float angle_th; //rad
// };


// void Base::init() {

//   // sensor init
//   sensor.init();

//   // motors init
//   motorL.init(LEFT);
//   motorR.init(RIGHT);
//   motors_on = false;

//   // positioning system initialisation
//   posx_th = 0;
//   posy_th = 0;
//   angle_th =0;
// }



// void Base::run(rundir dir) {
//   if(dir != STOP) {
//     motors_on = true;
    
//     motorL.run(dir);
//     motorR.run(dir);

//     motors_start_time = millis();
//   }
//   else if(dir == STOP && motors_on){
    

//     motorL.run(dir);
//     motorR.run(dir);
//     motors_on = false;

//     // distance travelled calculation
//     unsigned long t = (millis() - motors_start_time) / 1000; // motors running time in seconds
//     //Serial.println(t);
//     float dist = ROBOT_SPEED_MS * t; // travelled distance in meters
//     // Serial.println(dist);


//     posx_th += dist*cos(angle_th);
//     posy_th += dist*sin(angle_th);


//   }
// }



// void Base::run_m(rundir dir, float d) {
//   /*Warning: this method is blocking*/

//   run(dir);
//   delayMicroseconds(d/ROBOT_SPEED_MS*1000000);
//   run(STOP);

//   // update position
//   posx_th += d*cos(angle_th);
//   posy_th += d*sin(angle_th);

// }


// void Base::turn_deg(side s, unsigned int a) {
//   float angle_rad = a* (3.14159)/180;
//   if(s == LEFT) angle_th += angle_rad;
//   else if(s == RIGHT) angle_th -= angle_rad; 

//   if(s == LEFT) {
//     motorL.run(BACKWARD);
//     motorR.run(FORWARD);
//     delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
//     motorL.run(STOP);
//     motorR.run(STOP);
//   }
//   else if(s == RIGHT) {
//     motorL.run(FORWARD);
//     motorR.run(BACKWARD);
//     delayMicroseconds(angle_rad/ROBOT_ANGULAR_SPEED_DEGS*1000000);
//     motorL.run(STOP);
//     motorR.run(STOP);
//   }
// }




// bool Base::proximity(unsigned int seuil) {
//   return sensor.proximity(seuil);
// }



// void Base::print_param(void) {
//   sensor.print_measure();
//   Serial.print("posx_th: ");
//   Serial.print(posx_th);
//   Serial.println(" m");
//   Serial.print("posy_th: ");
//   Serial.print(posy_th);
//   Serial.println(" m");
//   Serial.print("Angle: ");
//   Serial.print(angle_th * 180 / (3.14159));
//   Serial.println(" °");

//   Serial.println();
// }







#include "Base.h"
#include "Arduino.h"





Base robot;


void setup() {

  while (!Serial) {}
  Serial.begin(9600); // a mettre la ou il y a des Serial.print dans les classes


  robot.init();

}


void loop()
{
  robot.run(FORWARD);

  while(!robot.proximity()) {
    robot.print_param();
  }

  robot.run(STOP);
  while(robot.proximity()) {
    robot.turn_deg(LEFT, 90);
  }

  
  robot.print_param();
  
}

