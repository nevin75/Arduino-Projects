//LED TEST 2 w/ 74HC595
//by Amanda Ghassaei 2012
//http://www.instructables.com/id/Multiplexing-with-Arduino-and-the-74HC595/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
*/

//this code will display the values of ledData across a 4x4 led matrix

//pin connections- the #define tag will replace all instances of "latchPin" in your code with A1 (and so on)
#define latchPin A1
#define clockPin A0
#define dataPin A2

 /*
 Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
 */
#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"

int valColumn;
int valRow;

WiiChuck chuck = WiiChuck();

//looping variables
byte i;
byte j;
int x;
int y;

//storage variable
byte dataToSend;

//storage for led states, 4 bytes
byte ledColumn[] = {~2, ~4, ~8, ~16, ~32, ~64, ~128};

char ledTime[8]={ 
                  {1,0,0,0,0,0,0,0,1},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {0,0,0,0,0,0,0,0,0},
                  {1,0,0,0,0,0,0,0,1}
                };
 
              

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  int ledData[8];
 }

void loop() {
  
  chuck.update();

 valColumn = chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
  valColumn = map(valColumn, 75, -80, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 
  valRow = chuck.readJoyY();            // reads the value of the potentiometer (value between 0 and 1023) 
  valRow = map(valRow, -70, 75, 0, 7);     // scale it to use it with the servo (value between 0 and 180)   
    // = { 
// 0b10000001,//this one missed
// 0b00000000,//this one duplicated
// 0b00000000,
// 0b00000000,//this one duplicated
// 0b00000000,
// 0b00000000,
// 0b00000000,
// 0b00000000, 
// };
 
// read sensors

 ledTime[valColumn][valRow] = (millis+3000)

for (x=0;x<8;x++) {
   for (y=0;y<8;y++){
    if (ledTime[x][y] <= millis)
  {bitwrite (ledData[x],[y],1)}
      else bitwrite (ledData[x],[y],0); 
   
 
  for (i=0;i<8;i++){
    
    //send data from ledData to each row, one at a time
    byte dataToSend = ledData[i]; // (1 << (i));// | (15 & ~ledColumn[i]);
      
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);
    // shift out the bits of dataToSend to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, dataToSend);
    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
      
  }  
}


