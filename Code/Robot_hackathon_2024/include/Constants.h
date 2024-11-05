/**
 * C'est dans ce fichier que les constantes pour régler les moteurs doivent être saisies
 */

#pragma once
/********************************************************
 * Constantes modifiables
 *******************************************************/


#define ROBOT_L_MOTOR_COEF 1 //speed coef for Left motor
#define ROBOT_R_MOTOR_COEF 0.95 //speed coef for Right motor

#define ROBOT_SPEED_COEF 0.95 //coefficient on the speed of the robot
#define ROBOT_ANGLUAR_SPEED_COEF 0.87 //coefficient on the rotation speed of the robot

#define ROBOT_WHEEL_SPACING_M 0.114 //robot space between wheels in m
#define ROBOT_SPEED_MS 0.14 //* ROBOT_SPEED_COEF //robot speed in m/s

/********************************************************
 * Constantes système - NE PAS MODIFIER
 *******************************************************/

#define MOTOR_G_STOP 1500
#define MOTOR_G_SPEED_RANGE 500

#define MOTOR_D_STOP 1500
#define MOTOR_D_SPEED_RANGE 500

#define ROBOT_ANGULAR_SPEED_RADS 2*ROBOT_SPEED_MS/ROBOT_WHEEL_SPACING_M * ROBOT_ANGLUAR_SPEED_COEF

/********************************************************
 * Pins et enums
 *******************************************************/

#define LED1 D10
#define LED2 D11
#define BOUTON_EQUIPE D13

typedef enum {LEFT, RIGHT} side_t;
typedef enum {STOP = 0, FORWARD, BACKWARD} rundir_t;