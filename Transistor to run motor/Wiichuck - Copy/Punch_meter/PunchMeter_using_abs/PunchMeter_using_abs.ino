/*
Nevin Danielson
Project: Wii Punch Meter
Last update October 18, 2013

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
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

WiiChuck chuck = WiiChuck();

//initialize variables to be used
int Movement;
int AccelAvg;
int Baseline;
int Count;
int Changepacked;

///////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //nunchuck_init();
  Serial.begin(115200);
  chuck.begin();
 
  // lcd init
  lcd.begin(16, 2);
 
 //set values
  Baseline = (abs(chuck.readAccelX()) + (abs(chuck.readAccelY())));
  Movement = 0;
  Count = 0;
  Changepacked = 0;
  AccelAvg = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////
void loop() {
   chuck.update();
  
  //Measure for a difference from standstill. 
  Movement = (abs(chuck.readAccelX())+ abs (chuck.readAccelY())) - Baseline;
   
      
 //if movement is significant, start counting   
    if (Movement > 10) Count = 1;
    
  //if counting, measure how much movement and cumulatively add them together
  if (Count > 0)
    {Changepacked = Changepacked + Movement;
      
     Count = Count + 1;
    }
 
 else 
   lcd.clear();
   lcd.setCursor (0, 0);
   lcd.print ("Ready");
 
 //once 10 readings have been added together
     
if (Count = 10)

//find the average amount for each of the 10 cycles
  {
      AccelAvg = (Changepacked / 10);     

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
           
    }
   
 else 
   lcd.setCursor(0, 0);
   lcd.print("Ready!"); 
   

   }

