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


//looping variables for recursive functions
int i, j;
short unsigned int ledData;
short unsigned int columnData;
short unsigned int ledData2;
short unsigned int columnData2;

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
 }

void loop() 
{
 
 
 //multiplex LEDs based on ledData per column
	for (i = 0; i < 8; i++)
	{
		ledData = 0;
		columnData = 0;
		ledData2 = 0;
		columnData2 = 0;
		bitWrite(ledData, i, 1);
		bitWrite(columnData, i, 1);

     // setlatch pin low so the LEDs don't change while sending in bits
      digitalWrite(latchPin, LOW);
     // shift out the bits of the ground, then the anode to the 74HC595
      shiftOut(dataPin, clockPin, LSBFIRST, ledData);
      shiftOut(dataPin, clockPin, LSBFIRST, columnData);
	  shiftOut(dataPin, clockPin, LSBFIRST, ledData2);
	  shiftOut(dataPin, clockPin, LSBFIRST, columnData2);
      
     //set latch pin high- this sends data to outputs so the LEDs will light up
      digitalWrite(latchPin, HIGH);
      delay (1);
    }
	for (i = 0; i < 8; i++)
	{
		ledData = 0;
		columnData = 0;
		ledData2 = 0;
		columnData2 = 0;
		bitWrite(ledData2, i, 1);
		bitWrite(columnData2, i, 1);

		// setlatch pin low so the LEDs don't change while sending in bits
		digitalWrite(latchPin, LOW);
		// shift out the bits of the ground, then the anode to the 74HC595
		shiftOut(dataPin, clockPin, LSBFIRST, ledData);
		shiftOut(dataPin, clockPin, LSBFIRST, columnData);
		shiftOut(dataPin, clockPin, LSBFIRST, ledData2);
		shiftOut(dataPin, clockPin, LSBFIRST, columnData2);

		//set latch pin high- this sends data to outputs so the LEDs will light up
		digitalWrite(latchPin, HIGH);
		delay(1);
	}
}

