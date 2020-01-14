 /*
 Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
 */

//Pin connected to ST_CP of 74HC595
int latchPin = A1;
//Pin connected to SH_CP of 74HC595
int clockPin = A0;
//Pin connected to DS of 74HC595
int dataPin = A2;

#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"

int valColumn;
int valRow;

WiiChuck chuck = WiiChuck();

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //  Serial.begin(115200);
chuck.begin();
//chuck.update();
//nunchuck_init();
  
}
 
void loop() {

//chuck.begin();
 chuck.update();

  valColumn = chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
  valColumn = map(valColumn, 120, -80, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 
  valRow = chuck.readJoyY();            // reads the value of the potentiometer (value between 0 and 1023) 
  valRow = map(valRow, -70, 75, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 

  int rowBitsToSend = 0;
  int columnBitsToSend = 0;
  digitalWrite(latchPin, LOW);
   bitWrite(columnBitsToSend, 0, 1); // Gives us 000000001 //green. ground. 0 creates a circuit. first byte to go in, gets pushed to second register
   bitWrite(columnBitsToSend, 1, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 2, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 3, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 4, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 5, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 6, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 7, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 8, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 9, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 10, 1); // Gives us 000000001 //green. ground. 0 creates a circuit. first byte to go in, gets pushed to second register
   bitWrite(columnBitsToSend, 11, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 12, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 13, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 14, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 15, 1); // Gives us 000000001
   
   
  bitWrite(columnBitsToSend, valColumn, 0); // Gives us 000000001

  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend); // Send the byte to the shift register which passes it to the second shift register
shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend); // Send the byte to the shift register which passes it to the second shift register

   bitWrite(rowBitsToSend, 0, 0 ); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 1, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 2, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 3, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 4, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 5, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 6, 0); // Adds on to the previous modified bits to give us 00001001 The two reds on the short end of the board are shorting.
   bitWrite(rowBitsToSend, 7, 0); // Gives us 00000001
    bitWrite(rowBitsToSend, 8, 0 ); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 9, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 10, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 11, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 12, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 13, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 14, 0); // Adds on to the previous modified bits to give us 00001001 The two reds on the short end of the board are shorting.
   bitWrite(rowBitsToSend, 15, 0); // Gives us 00000001
     bitWrite(rowBitsToSend, valRow, 1); // Gives us 00000001


 shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
 shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
 digitalWrite(latchPin, HIGH); // Tell the shift register we are done sending data so it can enable the outputs
//  delay(50); // Not really necessary in this example but it will be for lighting up multiple columns
}
