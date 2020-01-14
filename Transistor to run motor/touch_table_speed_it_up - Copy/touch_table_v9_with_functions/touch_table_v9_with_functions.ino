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
int valColumn, valRow;


//name an array to hold all the led boolean info
byte ledData[8];

//looping variables for recursive functions
int i, j, x, y;

//Nunchck initialization?
WiiChuck chuck = WiiChuck();


//store a static array for led columns to be grounded in the POV cycle - one ground (not a 1) in each array
int ledColumn[] = {127, 191,223,239,247,251,253,254};

// set a long variable to capture an 8 unit array of milliseconds (one variable for each LED in a column)
unsigned long ledTimes[8][8] ;

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  int ledData[8];
  //assign each of the arrays of LED column times to a specific variable in ledTimes (it becomes a pointer)
 
  chuck.begin();
  chuck.update();
 }

void loop() 
{
readChuck (ledTimes);
dataPrep (ledTimes[0]);
void displayLEDs ();
}

long unsigned* dataPrep (unsigned long ledTimes[])
{
  ledData[0]=0;
  ledData[1]=0;
  ledData[2]=0;
  ledData[3]=0;
  ledData[4]=0;
  ledData[5]=0;
  ledData[6]=0;
  ledData[7]=0;
  
 //mark a positive LED boolean state (1) wherever the coordinates have a current timestamp  
  for  (x = 0; x<8; x++) //on each column of LEDs....
    {for (y = 0; y<8; y++) //on each LED in that column... 
      {if (ledTimes[x][y] >= millis())// check if it is still current
        {bitWrite(ledData[x], y, 1);}// set that individual bit to on.
     }
   }
return ledTimes
}  
unsigned long readChuck (unsigned long ledTimes[8][8])
{ //get wiichuck data and current LED coordinate
  chuck.update();
  valColumn = map(chuck.readJoyX(), 131, -124, 0, 7);
  valRow = map(chuck.readJoyY(), 123, -132, 0, 7);          //scale it to a 0-7 range

 //timestamp the current led
  ledTimes[valColumn][valRow] = (millis() + 10000);
  return ledTimes
}
void displayLEDs ()
{for (i = 0; i<8; i++) 
    {
     // setlatch pin low so the LEDs don't change while sending in bits
      digitalWrite(latchPin, LOW);
     // shift out the bits of the ground, then the anode to the 74HC595
      shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
      shiftOut(dataPin, clockPin, LSBFIRST, ledData[i]);
     //set latch pin high- this sends data to outputs so the LEDs will light up
      digitalWrite(latchPin, HIGH);
      delay (1);
    }
}





   
