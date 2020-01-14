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

#include <LiquidCrystal.h>
#include<String.h>    

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //nunchuck_init();
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  lcd.begin(16, 2);
  

}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
   chuck.update(); 
  lcd.clear(); lcd.print("Ready!");
  //print nunchuck state to serial monitor
  PrintWiiChuck();

   
   if ((chuck.readAccelX())> 200) delay (4000);
   else delay (100);
 }

///////////////////////////////////////////////////////////////////////////////////////////
  //print nunchuck state to serial monitor
void PrintWiiChuck(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Punch Meter");
  lcd.setCursor(0, 1);
  lcd.print(format(chuck.readAccelZ())) + (format(chuck.readAccelX())) + (format(chuck.readAccelY())); 

    }




///////////////////////////////////////////////////////////////////////////////////////////
String format(const float inp){
 String sign,val;
 if(inp<0)
   sign="-";
 else
   sign=" ";
   
 int absol=abs(inp);
 if (absol<10)
   val="  "+String(absol);
 else if (absol<100 && absol>9)
   val=" "+String(absol);
 else
   val=String(absol);
   
 String outpt=sign+val;
 return outpt;
} 
