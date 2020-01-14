#include <WiiChuck.h>
#include <WiiChuck_bkp.h>

/*
  LiquidCrystal Library - Serial Input
 
// include the library code:
*/
#include <LiquidCrystal.h>

#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"


WiiChuck chuck = WiiChuck();
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
 
  //nunchuck_init();
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
    // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);
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
void PrintWiiChuck(){
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
