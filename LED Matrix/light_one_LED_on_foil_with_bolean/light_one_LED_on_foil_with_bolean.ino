
#include <CapacitiveSensor.h>
#include<String.h>            
#include "Wire.h"

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin, add a wire and or foil

int latchPin = A1;
int clockPin = A0;
int dataPin = A2;

//long time = 0;
//int state = HIGH;

int maxval = 2000;
int incrementrow = 20;
int incrementcolumn = 40;

int valColumn;
int valRow;

//int debounce = 200;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
 }
 
void loop() {
    long start = millis();  //DO I NEED THIS?
    long total1 =  cs_4_2.capacitiveSensor(10);
    long total2 =  cs_4_6.capacitiveSensor(10);
  //  long total3 =  cs_4_8.capacitiveSensor(30);
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    Serial.print(total1);                  // print sensor output 1
    Serial.print("\t");
    Serial.println(total2);                  // print sensor output 2
    Serial.print("\t");
  //  Serial.println(total3);                // print sensor output 3
    delay(10);                             // arbitrary delay to limit data to serial port 



   if (total1 > (incrementcolumn * 7)) {valColumn = 7;}
else if (total1 > (incrementcolumn * 6)) {valColumn = 6;}
else if (total1 > (incrementcolumn * 5)) {valColumn = 5;}
else if (total1 > (incrementcolumn * 4)) {valColumn = 4;}
else if (total1 > (incrementcolumn * 3)) {valColumn = 3;}
else if (total1 > (incrementcolumn * 2)) {valColumn = 2;}
else if (total1 > incrementcolumn) {valColumn = 1;}
else if (total1 > 0) {valColumn = 0;}
else {valColumn = 10;}

  if (total2 > (incrementrow * 7)) {valRow = 7;}
else if (total2 > (incrementrow * 6)) {valRow = 6;}
else if (total2 > (incrementrow * 5)) {valRow = 5;}
else if (total2 > (incrementrow * 4)) {valRow = 4;}
else if (total2 > (incrementrow * 3)) {valRow = 3;}
else if (total2 > (incrementrow * 2)) {valRow = 2;}
else if (total2 > incrementrow) {valRow = 1;}
else if (total2 > 0) {valRow = 0;}
else {valRow = 10;}

    
 
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

}
