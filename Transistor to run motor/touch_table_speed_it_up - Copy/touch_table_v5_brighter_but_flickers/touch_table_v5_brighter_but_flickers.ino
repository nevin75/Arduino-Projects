 /*this code will respond to sensor input to light the corresponding LED on a matrix 
for 3 seconds, possibly multiple LEDs at a time.

pin connections- the #define tag will replace all instances of 
"latchPin" in your code with A1 (and so on)
*/
#define latchPin A1
#define clockPin A0
#define dataPin A2

#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"

/*
Notes:
Wii Nunchuck Configuration:
Data = pin A4
CLK = pin A5
*/


// variables for what coordinates are being indicated by the WiiChuck
int valColumn;
int valRow;

// variables for a baseline location for the WiiChuck. Compare to this 
//"control" to see if there's any movement.
int baseValColumn;
int baseValRow;

//name an array to hold all the led boolean info
byte ledData[8];

//looping variables for recursive functions
int i;
int j;
int x;
int y;
int timecompare;

//Nunchck initialization?
WiiChuck chuck = WiiChuck();

//storage variable to send to daisy-chained shift register. 
//Prepped byte for each column gets put here in the recursive loop.
//int dataToSend;

//store a static array for led columns to be grounded in the POV cycle - one ground (not a 1) in each array
int ledColumn[] = { 127, 191,223,239,247,251,253,254};
// set a long variable to capture an 8 unit array of milliseconds (one variable for each LED in a column)
unsigned long ledTimes[8][8] ;


// set an array that points to each of the 8 variable arrays in "ledTime0-7"



void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  int ledData[8];
  //assign each of the arrays of LED column times to a specific variable in ledTimes (it becomes a pointer)
 
 chuck.begin();
  chuck.update();

    // put X in a Column variable
   valColumn = chuck.readJoyX();// reads the value of the potentiometer (value between 0 and 1023) 
    valColumn = map(valColumn, 131, -124, 0, 7);      // scale it to a 0-7 range
    valRow = chuck.readJoyY();                 // put Y in a Row variable
    valRow = map(valRow, 123, -132, 0, 7);          //scale it to a 0-7 range

     //remember the "control" values so we can test it next cycle
        baseValColumn = valColumn;
        baseValRow = valRow;

 
}

void loop() {


//for (i = 0; i<8; i++) {
  // setlatch pin low so the LEDs don't change while sending in bits
 //  digitalWrite(latchPin, LOW);

  // shift out the bits of the ground, then the anode to the 74HC595
//  shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
 // shiftOut(dataPin, clockPin, LSBFIRST, ledData[i]);
  //set latch pin high- this sends data to outputs so the LEDs will light up
 // digitalWrite(latchPin, HIGH);
 // delay (10);//???? time to regen power?
//}
  // get wiichuck data
chuck.begin();
chuck.update();
//Serial.print("done chuck update initialization");
//Serial.println();
    // put X in a Column variable
    valColumn = chuck.readJoyX();// reads the value of the potentiometer (value between 0 and 1023) 
    valColumn = map(valColumn, 131, -124, 0, 7);      // scale it to a 0-7 range
    valRow = chuck.readJoyY();                 // put Y in a Row variable
    valRow = map(valRow, 123, -132, 0, 7);          //scale it to a 0-7 range


for (i = 0; i<8; i++) {
  // setlatch pin low so the LEDs don't change while sending in bits
   digitalWrite(latchPin, LOW);

// shift out the bits of the ground, then the anode to the 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
  shiftOut(dataPin, clockPin, LSBFIRST, ledData[i]);
  //set latch pin high- this sends data to outputs so the LEDs will light up
  digitalWrite(latchPin, HIGH);
  delay (15);//???? time to regen power?
}                       //test if anything has changed
  if (valColumn > baseValColumn || valRow < baseValRow ||valColumn < baseValColumn || valRow > baseValRow)
    { 
      ledTimes[valColumn][valRow] = (millis() + 3000);
    }
//for (i = 0; i<8; i++) {
  // setlatch pin low so the LEDs don't change while sending in bits
//   digitalWrite(latchPin, LOW);
  // shift out the bits of the ground, then the anode to the 74HC595
//  shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
//  shiftOut(dataPin, clockPin, LSBFIRST, ledData[i]);
  //set latch pin high- this sends data to outputs so the LEDs will light up
//  digitalWrite(latchPin, HIGH);
//  delay (10);//???? time to regen power?
//}
 /*update LED boolean state with current millis info
  */
   for  (x = 0; x<8; x++) //on each column of LEDs....
  { for (y = 0; y<8; y++) //on each LED in that column... 
    { if (ledTimes[x][y] >= millis())// check if it is still current
    {
     bitWrite(ledData[x], y, 1);// set the individual bit to on.
  
    }
     else bitWrite(ledData[x], y, 0);// or set it to off
    }
  }
/* start a cycle of actual lighting
 multiplex LEDs
*/
for (i = 0; i<8; i++) {
  // setlatch pin low so the LEDs don't change while sending in bits
   digitalWrite(latchPin, LOW);
  // shift out the bits of the ground, then the anode to the 74HC595
  shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
  shiftOut(dataPin, clockPin, LSBFIRST, ledData[i]);
  //set latch pin high- this sends data to outputs so the LEDs will light up
  digitalWrite(latchPin, HIGH);
  delay (15);//???? time to regen power?
                }
  
}












  



