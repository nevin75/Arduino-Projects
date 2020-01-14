/*
 Name:    16x16.ino
 Created: 9/21/2015 4:43:57 PM
 Author:  Nevin.Danielson
*/

/*this code tests the shift register and transistor circuitry on a 16x16 LED matrix. It should create a 
//diagonal line.

pin connections- the #define tag will replace all instances of
"latchPin" in your code with A1 (and so on)
*/
#define latchPin A1
#define clockPin A0
#define dataPin A2

#include<String.h>            

//looping variables for recursive functions
int i;
char ledData;
char ledData2;
char columnData; 
char columnData2;

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}


void loop()
{

  //updateMatrix();
  //multiplex LEDs based on ledData per column
  //shiftOut is limited to 8 bits, so we do it once for the primary variables, 
  //then a second time for the 2nd variables
  for (i = 0; i<8; i++)
  {
    ledData = 0;
    columnData = 0; 
    ledData2 = 8;
    columnData2 = 16;
    bitWrite(ledData, /*i*/2, 1);
    bitWrite(columnData,  /*i*/2, 1);
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);
    // shift out the bits of the ground, then the anode to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, ledData);
    shiftOut(dataPin, clockPin, LSBFIRST, ledData2);
    shiftOut(dataPin, clockPin, LSBFIRST, columnData);
    shiftOut(dataPin, clockPin, LSBFIRST, columnData2);

    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
    delay(1);
  }
  
  //only difference is that we're writing to variable'2'
  for (i = 0; i<8; i++)
  {
    ledData = 8;
    columnData = 16;
    ledData2 = 0;
    columnData2 = 0;
    bitWrite(ledData2, /*i*/2, 1);
    bitWrite(columnData2, /*i*/2, 1);
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);
    // shift out the bits of the ground, then the anode to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, ledData);
    shiftOut(dataPin, clockPin, LSBFIRST, ledData2);
    shiftOut(dataPin, clockPin, LSBFIRST, columnData);
    shiftOut(dataPin, clockPin, LSBFIRST, columnData2);

    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
    delay(1);
  }
}

