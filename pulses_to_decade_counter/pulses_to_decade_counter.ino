
#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();
/*  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
*/
                                        // map LEDs for four directions to corresponding pin

int pulsePin = 7;

                                        //create simple names to hold the X and Y interger readings from the joystick (from -100 to 100)
int xJoy;
int yJoy;
int pitch;
///////////////////////////////////////////////  
void setup() 

{     
                                        // initialize the digital pins as outputs (for the LEDs)
  pinMode(pulsePin, OUTPUT);     
 
  
                                        // initialize wiichuck
  
   chuck.begin();

   digitalWrite(pulsePin, LOW);

 }
 
/////////////////////////////////////
void loop() {
  
 chuck.update();                       //check the wiichuck for new data
 
 xJoy = chuck.readJoyX();              // puts the current value of the x (left-right) axis in the xJoy holder
 

     while (xJoy < -10)                           //if the X reading was negative,
      {
       digitalWrite(pulsePin, HIGH);
       delay (200);
       digitalWrite (pulsePin, LOW);
       delay (200); 
      }
       while (xJoy > 10)                           //if the X reading was positive,
      {
       digitalWrite(pulsePin, HIGH);
       delay (20);
       digitalWrite (pulsePin, LOW);
       delay (20); 
      }
  
  // }
//  else                                 //if there wasn't a signficant reading in the first place, 
  //     digitalWrite(ledleft, LOW);       // turn the Left LED off
  //     digitalWrite(ledright, LOW);      // turn the Right LED off
  
yJoy = chuck.readJoyY();              // puts the current value of the y (up-down) axis in the yJoy holder          

//while (abs(yJoy) > 10)                   //if the Y reading is significant, continue on
 //{
  //  if (yJoy > 10)                        //If the Y reading was positive, 
   //   { 
  //      digitalWrite(ledup, HIGH);           // turn the LED on (HIGH is the voltage level)
  //    } 
  //   else                                 //if the Y reading wasn't positive,
  //    {
  //      digitalWrite(ledup, LOW);            // turn the Up LED off (LOW is the voltage level)
  //    }
  //  if (yJoy < -10)                       //if the Y reading was negative,
  //    {
  //      digitalWrite(leddown, HIGH);         // turn the Down LED on (HIGH is the voltage level)
  //    }
  //  else                                 //if the Y reading wasn't negative, 
  //    {
  //     digitalWrite(leddown, LOW);           // turn the Down LED off (LOW is the voltage level)
  //    }
 
   
 if (chuck.buttonC)
   {digitalWrite (pulsePin, HIGH);
   delay (3);
   digitalWrite (pulsePin, LOW);}

}

//pitch = (chuck.readAccelX() + chuck.readAccelY() + chuck.readAccelZ());   
  // if (chuck.buttonZ)
   //  {tone(7, pitch, 20);}
  // else
   //   {digitalWrite(speakerPin, LOW);}
//delay(1);   
//}
  //else                               //if the Y reading wasn't significant, 
  //     digitalWrite(ledup, LOW);         // turn the Up LED off
  //     digitalWrite(leddown, LOW);       // turn the Down LED off
//}
