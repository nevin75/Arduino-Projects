/*
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//tempeter
int val;
int dat;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
}

void loop() {
  val=analogRead(0);
  dat=(125*val)>>8; //计算温度值

  lcd.setCursor(0,0);
  lcd.print("Tep: ");
  lcd.setCursor(6,0);
  lcd.print(dat);
  lcd.setCursor(10,0);
  lcd.print("'C");
  delay(10);
  lcd.setCursor(0,1);
  if(dat>18)
  {
    lcd.print("Warm! B2CQSHOP");
  }
  else
  {
    lcd.print("Cold! B2CQSHOP");
  }
  
  delay(500);
}


