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

struct Setting {
  Setting(Data data);
  byte temper = 0;
  byte humi = 0;
  Data data;
  
  


  
  bool setTemperDelta(byte _delta_T);
  bool setHumi(byte _humi);
  bool setHumiDelta(byte _delta_H);
};

struct Command {
  static void radiatorSwap();
  static void humiSwap();
  static void ventInSwap();
  static void pompaSwap();
};



#endif
