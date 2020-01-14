/*
Lee Sichello
200259098
CS 207
Project: Wii Labyrinth
Last update Nov 7, 2012

Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
 */

#include<String.h>
#include "Wire.h"
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();

///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //nunchuck_init();
  Serial.begin(9600);
  chuck.begin();
  chuck.update();
}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  chuck.update();

  //print nunchuck state to serial monitor
  PrintWiiChuck();

  delay(400);
}

///////////////////////////////////////////////////////////////////////////////////////////
//print nunchuck state to serial monitor
void PrintWiiChuck() {
  Serial.print("Roll:");
  Serial.print(format(chuck.readRoll()));
  Serial.print(", ");
  Serial.print("Pitch:");
  Serial.print(format(chuck.readPitch()));
  Serial.print(", ");

  Serial.print("AccelX:");
  Serial.print(format(chuck.readAccelX()));
  Serial.print(", ");
  Serial.print("AccelY:");
  Serial.print(format(chuck.readAccelY()));
  Serial.print(", ");
  Serial.print("AccelZ:");
  Serial.print(format(chuck.readAccelZ()));
  Serial.print(", ");

  Serial.print("JoyX:");
  Serial.print(format(chuck.readJoyX()));
  Serial.print(", ");
  Serial.print("JoyY:");
  Serial.print(format(chuck.readJoyY()));
  Serial.print(", ");

  if (chuck.buttonZ) {
    Serial.print("Z");
  } else  {
    Serial.print("-");
  }

  Serial.print(", ");

  //not a function//  if (chuck.buttonC()) {
  if (chuck.buttonC) {
    Serial.print("C");
  } else  {
    Serial.print("-");
  }
  Serial.println();

}

///////////////////////////////////////////////////////////////////////////////////////////
String format(const float inp) {
  String sign, val;
  if (inp < 0)
    sign = "-";
  else
    sign = " ";

  int absol = abs(inp);
  if (absol < 10)
    val = "  " + String(absol);
  else if (absol < 100 && absol > 9)
    val = " " + String(absol);
  else
    val = String(absol);

  String outpt = sign + val;
  return outpt;
}
