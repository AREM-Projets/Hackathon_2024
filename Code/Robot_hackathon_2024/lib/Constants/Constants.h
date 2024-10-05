/*
C'est dans ce fichier que les constantes pour régler les moteurs doivent être saisies
*/


#pragma once

#define TOF_XSDN D3

#define MOTOR_G_BACKWARD_STOP 1500//1475
#define MOTOR_G_FORWARD_STOP 1500//1575
#define MOTOR_G_SPEED_RANGE 500//50

#define MOTOR_D_BACKWARD_STOP 1500//1565
#define MOTOR_D_FORWARD_STOP 1500//1465
#define MOTOR_D_SPEED_RANGE 500//50

#define ROBOT_SPEED_MS 0.1174 //robot speed in m/s
#define ROBOT_WHEEL_SPACING_M 0.114 //robot space between wheels in m
#define ROBOT_ANGLUAR_SPEED_COEF 0.95 //angular speed correction coefficient

#define ROBOT_ANGULAR_SPEED_DEGS 2*ROBOT_SPEED_MS/ROBOT_WHEEL_SPACING_M * ROBOT_ANGLUAR_SPEED_COEF



typedef enum {LEFT, RIGHT} side;
typedef enum {FORWARD, BACKWARD, STOP} rundir;