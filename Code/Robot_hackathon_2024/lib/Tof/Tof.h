#pragma once

#include "Constants.h"
#include <VL53L1X.h>


class Tof
{
  /*Classe pour encapsuler les commandes pour faire fonctionner le tof dans un format plus proche du arduino. La méthode init simplifie l'initialisation avec le xsdn...*/
public:
  void init(void);
  bool proximity(unsigned int seuil);
  void print_measure(void);


private:
  VL53L1X sensor;
};
