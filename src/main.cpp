#include <LiquidCrystal.h>
#include "LiquidMenu.h"


#include "model.hpp"
#include "conf.hpp"
#include "func.h"



void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  radioSetup();
  delay(50);
  val[0] = 1;
  radioRequest(val);
delay(50);
  resiveData();


  settingTemHumi_screen.set_focusPosition(Position::LEFT);
  humiRadiatirState_screen.set_focusPosition(Position::LEFT);
  ventInPompaState_screen.set_focusPosition(Position::LEFT);

  temperSet_screen.set_focusPosition(Position::LEFT);
  humiSet_screen.set_focusPosition(Position::LEFT);
  temperSet_screen0.set_focusPosition(Position::LEFT);
  temperSet_screen1.set_focusPosition(Position::LEFT);
  temperSet_screen2.set_focusPosition(Position::LEFT);
  temperSet_screen3.set_focusPosition(Position::LEFT);

  temperS_line.attach_function(1, funcSetTemp);
  humiS_line.attach_function(1, funcSetHumi);
  humiState_line.attach_function(1, humiSwap);
  temperSet_line1.attach_function(1, funcSetTemp1);
  temperSet_line2.attach_function(1, funcSetTemp2);
  humiSet_line1.attach_function(1, funcSetHumi1);
  humiSet_line2.attach_function(1, funcSetHumi2);
  radiatorState_line.attach_function(1, radiatorSwap);
  humiState_line.attach_function(1, humiSwap);
  ventIn_line.attach_function(1, ventInSwap);
  pompa_line.attach_function(1, pompaSwap);





  humiState_line.attach_function(1, humiSwap);
  ventIn_line.attach_function(1, ventInSwap);
  pompa_line.attach_function(1, pompaSwap);
  menu.add_screen(welcome_screen1);
  menu.add_screen(settingTemHumi_screen);
  menu.add_screen(humiRadiatirState_screen);
  menu.add_screen(ventInPompaState_screen);
  menu.add_screen(soil_screen);
  menu.add_screen(temperSet_screen);
  menu.add_screen(humiSet_screen);
  menu.add_screen(temperSet_screen0);
  menu.add_screen(temperSet_screen1);
  menu.add_screen(temperSet_screen2);
  menu.add_screen(temperSet_screen3);
  menu.update();
}

void loop() {

  if (starttime == 0){
    starttime = millis();
resiveData();
  }
  if (millis() - Period >= starttime && millis() > Period) {
    val[0] = 1;
   radioRequest(val);

   resiveData();

    menu.update();

    // if (1) {
    //   radioRequest(2);
    //   resiveSettings();
    // }

    starttime = millis();
  }

  buttonsCheck();




}
