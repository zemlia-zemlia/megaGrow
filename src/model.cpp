
#include "model.hpp"

Setting::Setting(Data _data){
  data = _data;

  
}

bool Setting::setTemperDelta(byte _delta_T) {
  data.delta_T = _delta_T;

    return true;

}
bool Setting::setHumi(byte _humi) {
  data.humi = _humi;

    return true;

}
bool Setting::setHumiDelta(byte _delta_H) {
  data.delta_H = _delta_H;

    return true;

}
void Command::radiatorSwap() { Serial.print("radiator"); }
void Command::humiSwap() {}
void Command::ventInSwap() {}
void Command::pompaSwap() {}





