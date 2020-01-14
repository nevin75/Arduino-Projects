 /*
 Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
 */

#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin, add a wire and or foil


void loop()                    
{


//Pin connected to ST_CP of 74HC595
int latchPin = A1;
//Pin connected to SH_CP of 74HC595
int clockPin = A0;
//Pin connected to DS of 74HC595
int dataPin = A2;

#include<String.h>            
#include "Wire.h"
//#include "WiiChuck.h"

int valColumn;
int valRow;
}
//WiiChuck chuck = WiiChuck();

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
    Serial.begin(115200);
//chuck.begin();
//chuck.update();
  //nunchuck_init();
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
 
}
 
void loop() {
 
      long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(10);
    long total2 =  cs_4_6.capacitiveSensor(10);
    long total3 =  cs_4_8.capacitiveSensor(10);

    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.print(total2);                  // print sensor output 2
    Serial.print("\t");
    Serial.println(total3);                // print sensor output 3

    delay(10);                             // arbitrary delay to limit data to serial port 
}
//chuck.update();

  valColumn = total1; //chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
  valColumn = map(valColumn, 1500, 700, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 
  valRow = total2; //chuck.readJoyY();            // reads the value of the potentiometer (value between 0 and 1023) 
  valRow = map(valRow, 15000, 4000, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 

  byte rowBitsToSend = 0;
  byte columnBitsToSend = 0;
  digitalWrite(latchPin, LOW);
   bitWrite(columnBitsToSend, 0, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 1, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 2, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 3, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 4, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 5, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 6, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 7, 1); // Gives us 000000001
  bitWrite(columnBitsToSend, valColumn, 0); // Gives us 000000001

  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend); // Send the byte to the shift register which passes it to the second shift register
   bitWrite(rowBitsToSend, 0, 0); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 1, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 2, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 3, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 4, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 5, 0); // Gives us 00000001
   bitWrite(rowBitsToSend, 6, 0); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 7, 0); // Gives us 00000001
     bitWrite(rowBitsToSend, valRow, 1); // Gives us 00000001



 shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
 digitalWrite(latchPin, HIGH); // Tell the shift register we are done sending data so it can enable the outputs
  delay(2); // Not really necessary in this example but it will be for lighting up multiple columns
}
