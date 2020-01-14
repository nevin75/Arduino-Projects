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
byte ledData;
byte columnData;
byte ledData2;
byte columnData2;

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
 }

void loop() 
{
 
 
 //multiplex LEDs based on ledData per column
	for (i = 0; i < 16; i++)
	{
	  ledData=0;
    columnData=0;
    ledData2=0;
    columnData2=0;
		if (i<8)
		  {
		  // bitWrite(ledData, 2, 1);
      // bitWrite(columnData, i, 1);
      }
     else		
    		{
    		 bitWrite(ledData2, (i-8), 1); // i will be in the 8 to 15 range. subtracting
		     bitWrite(columnData2, (i-8), 1);
		    }

     // setlatch pin low so the LEDs don't change while sending in bits
      digitalWrite(latchPin, LOW);
     // shift out the bits the 74HC595. First bit in will go all the way to the last register, eight spot
      shiftOut(dataPin, clockPin, LSBFIRST, columnData2); //first eight will get pushed all the way to the end
      shiftOut(dataPin, clockPin, LSBFIRST, ledData2); //will get pushed to second-last register
      shiftOut(dataPin, clockPin, LSBFIRST, columnData); // will get pushed to second register
      shiftOut(dataPin, clockPin, LSBFIRST, ledData);  // will sit in the first register
      
     //set latch pin high- this sends data to outputs so the LEDs will light up
      digitalWrite(latchPin, HIGH);
      delay (1);
    }
}

