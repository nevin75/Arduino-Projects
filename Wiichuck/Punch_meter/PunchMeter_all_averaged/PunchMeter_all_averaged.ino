/*
Nevin Danielson
Project: Wii Punch Meter
Last update July 7, 2013

With HUGE coding assistance (and copying) from Lee Sichello

Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
 */
//include libraries
#include<String.h>
#include "Wire.h"
#include "WiiChuck.h"
WiiChuck chuck = WiiChuck();
#include <LiquidCrystal.h>
#include<String.h>    
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//initialize variables to be used
int Movement;
int AccelAvg;
int baselineX;
int baselineY;
int baselineZ;
int Xchange;
int Ychange;
int Zchange;
int Count;
int Xpacked;
int Ypacked;
int Zpacked;

///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //nunchuck_init();
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
 // lcd init
  lcd.begin(16, 2);
 
 //set values
  baselineX = chuck.readAccelX();
  baselineY = chuck.readAccelY();
  baselineZ = chuck.readAccelZ();
  Movement = 0;
  Count = 0;
  Xpacked = 0;
  Ypacked = 0;
  Zpacked = 0;
  AccelAvg = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
   chuck.update();
  
  //Measure the difference between standstill and movement. Subtract 1265 to bring it close to zero.
  Xchange = chuck.readAccelX() - baselineX;
  if (Xchange < 0) Xchange = Xchange * -1;
  
   Ychange = chuck.readAccelY() - baselineY;
  if (Ychange < 0) Ychange = Ychange * -1;
  
   Zchange = chuck.readAccelZ() - baselineZ;
  if (Zchange < 0) Zchange = Zchange * -1;
  
   Movement =  Xchange + Ychange + Zchange - 1265;
    
 //if movement is significant, start counting   
    if (Movement > 200) Count = 1;
    
    //if counting, measure difference from baseline and cumulatively add them together
  if (Count > 0)
    {
      Xchange = chuck.readAccelX() - baselineX;
          if (Xchange < 0) Xchange = Xchange * -1;
  
      Ychange = chuck.readAccelY() - baselineY;
          if (Ychange < 0) Ychange = Ychange * -1;
  
      Zchange = chuck.readAccelZ() - baselineZ;
          if (Zchange < 0) Zchange = Zchange * -1;
          
      Xpacked = Xpacked + Xchange;
      Ypacked = Ypacked + Ychange;
      Zpacked = Zpacked + Zchange;
      
      Count = Count + 1;
    }
 
 //once 10 readings have been added together
     
if (Count > 9)

//find the average amount for each of the 10 cycles, subtracting 1265 to report a manageable number for my eight year-old to read

  {
      AccelAvg = (Xpacked + Ypacked + Zpacked) / 10 - 2100;     

//Determine which message to print
        if (AccelAvg > 700) 
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Knockout!");
            lcd.setCursor(0, 1);
            lcd.print(AccelAvg);  
            delay (4000);
            lcd.clear();
          }
    
      else  if (AccelAvg > 400)
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Ouch!");
            lcd.setCursor(0, 1);
            lcd.print(AccelAvg); 
            delay (4000);
            lcd.clear();
        }
    
      else   if (AccelAvg > 300) 
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Good One!");
            lcd.setCursor(0, 1);
            lcd.print(AccelAvg); 
            delay (4000);
            lcd.clear();
          }
    
    else if (AccelAvg > 200 ) 
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("So Gentle.");
            lcd.setCursor(0, 1);
            lcd.print(AccelAvg); 
            delay (4000);
            lcd.clear();
          }
    
   
      Count = 0;
      lcd.clear();
     
    }
   
 else 
   lcd.setCursor(0, 0);
   lcd.print("Ready!"); 
   

   }

