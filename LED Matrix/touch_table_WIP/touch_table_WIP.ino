
/*

 
*/

//this code will respond to sensor input to light the corresponding LED on a matrix for 3 seconds, possibly multiple LEDs at a time.

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
int baseValColumn;
int baseValRow;
byte ledData[8];

WiiChuck chuck = WiiChuck();

//looping variables
byte i;
byte j;
int x;
int y;

//storage variable for which lights in each column should be on
byte dataToSend;

//storage for led columns to be grounded in the POV cycle
byte ledColumn[] = {~2, ~4, ~8, ~16, ~32, ~64, ~128};

unsigned long ledTime0[8];
unsigned long ledTime1[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime2[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime3[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime4[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime5[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime6[8]= {0,0,0,0,0,0,0,0};
unsigned long ledTime7[8]= {0,0,0,0,0,0,0,0};

unsigned long* ledTimes[8];

unsigned long* column;
unsigned long* coordinates;               
 
              

void setup() {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  int ledData[8];
  ledTimes[0]=ledTime0;    
  ledTimes[1]=ledTime1;     
  ledTimes[2]=ledTime2;     
  ledTimes[3]=ledTime3;       
  ledTimes[4]=ledTime4;     
  ledTimes[5]=ledTime5;      
  ledTimes[6]=ledTime6;    
  ledTimes[7]=ledTime7;       

    chuck.update();

 // put X in a Column variable
 valColumn = chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
 // scale it to a 0-7 range
  valColumn = map(valColumn, 75, -80, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 
  // put Y in a Row variable
  valRow = chuck.readJoyY();            // reads the value of the potentiometer (value between 0 and 1023) 
  //scale it to a 0-7 range
  valRow = map(valRow, -70, 75, 0, 7);     // scale it to use it with the servo (value between 0 and 180)   

   //remember the values so we can test it next cycle
 baseValColumn=valColumn;
baseValRow=valRow;
 }
 
void loop() {
  
readchuck;//will call setTime function if anything has changed
updatedisplay;//will review each led in array to see if anything is now on or timed out
lightDisplay();//ledData);// when all the setting is done
}
 
void lightDisplay(){//(ledData) {

// start a cycle of actual lighting
// for each column
  for (i=0;i<8;i++){
    
    //prepare a byte so it is the one that is grounded    
    byte dataToSend = ledData[i]; 
      
    // setlatch pin low so the LEDs don't change while sending in bits
    digitalWrite(latchPin, LOW);

     // shift out the bits of dataToSend to the 74HC595
    shiftOut(dataPin, clockPin, LSBFIRST, ledColumn[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, dataToSend);
    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
      
  }  
}
 
 long unsigned setTime () {
(ledTimes[valColumn])[valRow]=(millis+3000); 
 
}

 void readchuck () {
 // get wiichuck data
 chuck.update();

 // put X in a Column variable
 valColumn = chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
 // scale it to a 0-7 range
  valColumn = map(valColumn, 75, -80, 0, 7);     // scale it to use it with the servo (value between 0 and 180) 
  // put Y in a Row variable
  valRow = chuck.readJoyY();            // reads the value of the potentiometer (value between 0 and 1023) 
  //scale it to a 0-7 range
  valRow = map(valRow, -70, 75, 0, 7);     // scale it to use it with the servo (value between 0 and 180)   
  //test if anything has changed
if (valColumn != baseValColumn | valRow != baseValRow)
      {setTime(valColumn)(valRow);}
  
 }
 


int updatedisplay() {
 
 //on each column....
 for (x=0;x<8;x++) {
      //on each LED in that column... 
      for (y=0;y<8;y++){
        // check if it is still current
        if (ledTimes[x][y] <= millis)
              // set it to on
              {bitwrite (ledData[x],[y],1)}
              // or set it to off
              else bitwrite (ledData[x],[y],0); }
                }
              }
 

}


