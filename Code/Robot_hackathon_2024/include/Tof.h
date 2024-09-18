#pragma once

#include "Constants.h"
#include <VL53L1X.h>


class Tof
{
public:
  void init(void);
  bool proximity(unsigned int seuil);
  void print_measure(void);


private:
  VL53L1X sensor;
};
