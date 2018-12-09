#ifndef MODEL_HPP
#define MODEL_HPP
#include "arduino.h"

struct Data{
  float temper = 0;
  float humi = 0;
  byte soil = 0;
  byte temperS = 0;
  byte delta_T =0;
  byte humiS = 0;
  byte delta_H = 0;
  bool Humi = false;
  bool Radiator = false;
  bool VentIn = false;
  bool Pompa = false;


};





#endif
