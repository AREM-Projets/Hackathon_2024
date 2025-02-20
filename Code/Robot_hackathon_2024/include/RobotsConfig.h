/*
* C'est dans ce fichier que se trouvent les configurations pour les robots sumo des 10 ans d'AREM
*/

#pragma once

#define ROBOT_VERT






#ifdef ROBOT_ORANGE
// Parechoc: Proue de bateau
#define LINEAR_SPEED 3
#define ROTATION_SPEED 3
#endif

#ifdef ROBOT_VERT
// Parechoc: Poing
#define LINEAR_SPEED 2.5
#define ROTATION_SPEED 3
#endif

#ifdef ROBOT_JAUNE
// Parechoc: Faucheuse
#define LINEAR_SPEED 3
#define ROTATION_SPEED 4
#endif

#ifdef ROBOT_ROUGE
// Parechoc: plan incline
#define LINEAR_SPEED 2
#define ROTATION_SPEED 2
#endif