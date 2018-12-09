bool setTemper(byte _temperS);
bool setDeltaT(byte _delta_t);
bool setHumi(byte _humiS);
bool setDeltaH(byte _delta_H);
void radiatorSwap();
void humiSwap();
void ventInSwap();
void pompaSwap();

void buttonsCheck() {
  byte key = keyRead();
  if (key == 5) {                    // right
    if (menu.currentScreen() == 7) { // temper setting
      temperS++;
      menu.update();
    }
    else if (menu.currentScreen() == 8) { // delta_T setting
      Serial.print(menu.currentScreen());
      delta_T++;
      menu.update();
    }
    else if (menu.currentScreen() == 9) { // humiS
      humiS++;

      menu.update();
    }
    else if (menu.currentScreen() == 10) { // delta_H
      delta_H++;

      menu.update();
    }

    else {
      menu.switch_focus();
    }

    delay(debounc);
  }
  if (key == 2) {                    // left
    if (menu.currentScreen() == 7) { // temper setting
      temperS--;
      menu.update();
    }
    else if (menu.currentScreen() == 8) { // delta_T setting
      delta_T--;
      menu.update();
    }
     else if (menu.currentScreen() == 9) {
      humiS--;
      menu.update();
    }
    else if (menu.currentScreen() == 10) {
     delta_H--;
     menu.update();
   }

    else {
    }
    delay(debounc);
  }
  if (key == 4) { // up
    if (menu.currentScreen() == 7 || menu.currentScreen() == 8 || menu.currentScreen() == 9 || menu.currentScreen() == 10) {
      menu.change_screen(settingTemHumi_screen);
    } else

      menu.previous_screen();
    delay(debounc);
  }
  if (key == 1) {                    // select *
    if (menu.currentScreen() == 7) { // temper setting
      setTemper(temperS);

      menu.change_screen(settingTemHumi_screen);
    }
    else if (menu.currentScreen() == 8) { // temper setting
      setDeltaT(delta_T);

      menu.change_screen(settingTemHumi_screen);
    }
    else if (menu.currentScreen() == 9) { // humi setting
      setHumi(humiS);

      menu.change_screen(settingTemHumi_screen);
    }
    else if (menu.currentScreen() == 10) { // humi setting
      setDeltaH(delta_H);

      menu.change_screen(settingTemHumi_screen);
    }

     else {

      menu.call_function(1);
       // Serial.print(menu.currentScreen());
    }
    delay(debounc);
  }
  if (key == 3) { // down
    if (menu.currentScreen() != 4)
      menu.next_screen();

    delay(debounc);
  }
}



void funcSetTemp() {
  menu.change_screen(temperSet_screen);

  menu.update();
}
void funcSetHumi() {
  menu.change_screen(humiSet_screen);
  menu.update();
}
void funcSetTemp1() {
  menu.change_screen(temperSet_screen0);
  menu.update();
}
void funcSetTemp2() {
  menu.change_screen(temperSet_screen1);
   // Serial.print(menu.currentScreen());
  menu.update();
}
void funcSetHumi1() {
  menu.change_screen(temperSet_screen2);
  menu.update();
}
void funcSetHumi2() {
  menu.change_screen(temperSet_screen3);
  menu.update();
}



// Checks all the buttons.

byte keyRead() {
  int val = analogRead(A0); // ожидаем нажатие кнопок
  if (val < 50)
    return 5; // право   0
  else if (val < 170 && val > 50)
    return 4; // верх  144
  else if (val < 400 && val > 170)
    return 3; // низ   330
  else if (val < 550 && val > 400)

    return 2; // лево  505
  else if (val < 800 && val > 550)
    return 1; // выбор 741
  else if (val <= 1023 && val > 800)
    return 0; // ничего
}

void radioSetup() {
  radio.begin();
  delay(2);
  radio.setChannel(60);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}
  void radioRequest(byte val[2]) {
  radio.stopListening();

  radio.openWritingPipe(pipe);
  radio.write(val, sizeof(val));

  radio.startListening();
}
void resiveData() {
  Data dataRadio;
  Serial.println("resiv");
  if (radio.available()) {
    Serial.println("rAaa");
    // проверяем не пришло ли чего в буфер.
    radio.read(
        &dataRadio,
        sizeof(dataRadio)); // читаем данные и указываем сколько байт читать
    delay(50);

    Serial.print(dataRadio.temper);
    Serial.print(";");
    Serial.print(dataRadio.humi);
    Serial.print(";");
    Serial.print(dataRadio.temperS);
    Serial.print(";");
    Serial.print(dataRadio.humiS);
    Serial.print(";");
    Serial.println(dataRadio.soil);
data = dataRadio;

    temper = data.temper;
    humi = data.humi;
    soil = data.soil;
    temperS = data.temperS;
    delta_T = data.delta_T;
    humiS = data.humiS;
    delta_H = data.delta_H;
    Radiator = data.Radiator ? "ON" : "OFF";
    Humi = data.Humi ? "ON" : "OFF";
    VentIn = data.VentIn ? "ON" : "OFF";
    Pompa = data.Pompa ? "ON" : "OFF";

  }
}

bool setTemper(byte _temperS) {

val[0] = 2;
val[1] = _temperS;
Serial.println(val[1]);
radioRequest(val);
temperS = data.temperS = _temperS;

    return true;

}
bool setDeltaT(byte _delta_t) {

val[0] = 3;
val[1] = _delta_t;
Serial.println(val[1]);
radioRequest(val);
delta_T = data.delta_T = _delta_t;

    return true;

}

bool setHumi(byte _humiS) {

val[0] = 4;
val[1] = _humiS;
Serial.println(val[1]);
radioRequest(val);
humiS = data.humiS = _humiS;

    return true;

}
bool setDeltaH(byte _delta_H) {

val[0] = 5;
val[1] = _delta_H;
Serial.println(val[1]);
radioRequest(val);
delta_T = data.delta_H = _delta_H;

    return true;

}
void radiatorSwap(){
  val[0] = 6;
  radioRequest(val);
  data.Radiator = data.Radiator ? false : true;
  Radiator = data.Radiator ? "ON" : "OFF";

}
void humiSwap(){
  val[0] = 7;
  radioRequest(val);
  data.Humi = data.Humi ? false : true;
  Humi = data.Humi ? "ON" : "OFF";
}
void ventInSwap(){
  val[0] = 8;
  radioRequest(val);
  data.VentIn = data.VentIn ? false : true;
  VentIn = data.VentIn ? "ON" : "OFF";
}
void pompaSwap(){
  val[0] = 9;
  radioRequest(val);
  data.Pompa = data.Pompa ? false : true;
  Pompa = data.Pompa ? "ON" : "OFF";
}
