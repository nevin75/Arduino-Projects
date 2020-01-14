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


void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
}

void loop() {

  lcd.setCursor(0,0); // 第一行第一个字符开始显示
  lcd.print("OK: ");

  lcd.setCursor(5,0); // 第一行第六个字符开始显示
  lcd.print("Arduino!");

  lcd.setCursor(0,1);  // 第一行第六个字符开始显示
  lcd.print("Yes,B2CQSHOP");

  delay(500);
}
