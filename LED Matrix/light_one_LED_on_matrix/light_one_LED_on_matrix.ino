
//Pin connected to ST_CP of 74HC595
int latchPin = A1;
//Pin connected to SH_CP of 74HC595
int clockPin = A0;
//Pin connected to DS of 74HC595
int dataPin = A2;
 
void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  byte rowBitsToSend = 0;
  byte columnBitsToSend = 0;
  digitalWrite(latchPin, LOW);
   bitWrite(columnBitsToSend, 0, 0); // Gives us 000000001
   bitWrite(columnBitsToSend, 1, 0); // Gives us 000000001
   bitWrite(columnBitsToSend, 2, 0); // Gives us 000000001
   bitWrite(columnBitsToSend, 3, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 4, 0); // Gives us 000000001
   bitWrite(columnBitsToSend, 5, 0); // Gives us 000000001
   bitWrite(columnBitsToSend, 6, 1); // Gives us 000000001
   bitWrite(columnBitsToSend, 7, 1); // Gives us 000000001
   
  shiftOut(dataPin, clockPin, MSBFIRST, columnBitsToSend); // Send the byte to the shift register which passes it to the second shift register

   bitWrite(rowBitsToSend, 0, 1); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 1, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 2, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 3, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 4, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 5, 1); // Gives us 00000001
   bitWrite(rowBitsToSend, 6, 1); // Adds on to the previous modified bits to give us 00001001
   bitWrite(rowBitsToSend, 7, 1); // Gives us 00000001
      
 shiftOut(dataPin, clockPin, MSBFIRST, rowBitsToSend); // Send the byte to the shift register
  
 digitalWrite(latchPin, HIGH); // Tell the shift register we are done sending data so it can enable the outputs
  //delay(2); // Not really necessary in this example but it will be for lighting up multiple columns
}
