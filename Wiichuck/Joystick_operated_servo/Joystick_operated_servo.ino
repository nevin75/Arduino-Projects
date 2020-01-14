  
/*
Lee Sichello
200259098
CS 207
Project: Wii Labyrinth
Last update Nov 7, 2012

Notes:
  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
  Servo = pin 9
 */


#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"
#include <Servo.h>


int val;

WiiChuck chuck = WiiChuck();

Servo myservo; // create servo object to control a servo

void setup()
{
  Serial.begin(115200);
  chuck.begin();
  chuck.update();
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
  //nunchuck_init();
 
  
  
}
void loop()
   {
  val = chuck.readJoyX();            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 

  }


