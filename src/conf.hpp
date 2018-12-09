
const byte LCD_RS = 8;
const byte LCD_E = 9;
const byte LCD_D4 = 4;
const byte LCD_D5 = 5;
const byte LCD_D6 = 6;
const byte LCD_D7 = 7;
#include <RF24.h> // https://github.com/maniacbug/RF24
#include <SPI.h>
#include <nRF24L01.h>
const uint64_t pipe = 0xF0F1F2F3F4AA; // индитификатор передачи, "труба"
RF24 radio(48, 49);                   // CE, CSN
int dataRadio[5] = {};
byte settingRadio[4] = {};
Data data;

Setting setting(data);
byte val[2];

Command command;
float temper = data.temper;
float humi = data.humi;
byte soil = data.soil;
byte temperS = data.temperS;
byte humiS = data.humiS;
byte delta_T = data.delta_T;
byte delta_H = data.delta_H;
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
unsigned long starttime = 0;
unsigned long Period = 10000;
int debounc = 500;

byte keyRead();


LiquidLine welcome_line1(1, 0, "temper ", temper);
LiquidLine welcome_line2(1, 1, "humi   ", humi);
LiquidScreen welcome_screen1(welcome_line1, welcome_line2); // 0

LiquidLine temperS_line(1, 0, "temperS ", temperS);
LiquidLine humiS_line(1, 1, "humiS   ", humiS);
LiquidScreen settingTemHumi_screen(temperS_line, humiS_line); // 1

LiquidLine humiState_line(1, 0, "humi:       ", data.Humi);
LiquidLine radiatorState_line(1, 1, "radiator:   ", data.Radiator);
LiquidScreen humiRadiatirState_screen(humiState_line, radiatorState_line); // 2

LiquidLine ventIn_line(1, 0, "ventIn:     ", data.VentIn);
LiquidLine pompa_line(1, 1, "Pompa:      ", data.Pompa);
LiquidScreen ventInPompaState_screen(ventIn_line, pompa_line); // 3

LiquidLine Soil_line(1, 0, "Soil    ", soil);

LiquidScreen soil_screen(Soil_line); // 4

LiquidLine temperSet_line1(1, 0, "temperS ", temperS);
LiquidLine temperSet_line2(1, 1, "delta_T ", delta_T);
LiquidScreen temperSet_screen(temperSet_line1, temperSet_line2); // 5

LiquidLine humiSet_line1(1, 0, "humiS   ", humiS);
LiquidLine humiSet_line2(1, 0, "delta_H ", delta_H);
LiquidScreen humiSet_screen(humiSet_line1, humiSet_line2); // 6

LiquidLine temperSet_line10(1, 0, "temperS ", temperS);
LiquidLine temperSet_line20(1, 1, "<   >  *set");
LiquidScreen temperSet_screen0(temperSet_line10, temperSet_line20); // 7

LiquidLine temperSet_line11(1, 0, "delta_T ", delta_T);
LiquidScreen temperSet_screen1(temperSet_line11, temperSet_line20); // 8

LiquidLine humiSet_line11(1, 0, "humiS ", humiS);
LiquidScreen temperSet_screen2(humiSet_line11, temperSet_line20); // 9

LiquidLine humiSet_line12(1, 0, "delta_H ", delta_H);
LiquidScreen temperSet_screen3(humiSet_line12, temperSet_line20); // 10

LiquidMenu menu(lcd);
