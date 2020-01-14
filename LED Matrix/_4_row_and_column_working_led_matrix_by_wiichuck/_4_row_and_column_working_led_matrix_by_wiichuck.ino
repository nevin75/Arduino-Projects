
#include<String.h>            
#include "Wire.h"
#include "WiiChuck.h"

WiiChuck chuck = WiiChuck();
/*  Wii Nunchuck Configuration:
      Data = pin A4
      CLK = pin A5
*/
                                        // map LEDs for four directions to corresponding pin
//int column1 = 17;
//int column2 = 16;
//int column3 = 0;
//int column4 = 1;
int column5 = 2;
int column6 = 3;
int column7 = 4;
int column8 = 5;
//int row1 = 6;
//int row2 = 7;
//int row3 = 8;
int row4 = 9;
int row5 = 10;
int row6 = 11;
int row7 = 12;
//int row8 = 13;
                                    
int xJoy;
int yJoy;
int xJoybase;
int yJoybase;
///////////////////////////////////////////////  
void setup() 

{     
                                        // initialize the digital pins as outputs (for the LEDs)
 //pinMode(column1, OUTPUT);   
 //pinMode(column2, OUTPUT);    
// pinMode(column3, OUTPUT);    
// pinMode(column4, OUTPUT);    
 pinMode(column5, OUTPUT);    
 pinMode(column6, OUTPUT);    
 pinMode(column7, OUTPUT);    
 pinMode(column8, OUTPUT); 
//pinMode(row1, OUTPUT);  
//pinMode(row2, OUTPUT);  
//pinMode(row3, OUTPUT);  
pinMode(row4, OUTPUT);  
pinMode(row5, OUTPUT);  
pinMode(row6, OUTPUT);  
pinMode(row7, OUTPUT);  
//pinMode(row8, OUTPUT);  
  
  
                                        // initialize wiichuck
  Serial.begin(115200);
  chuck.begin();

 }
 
/////////////////////////////////////
void loop() {
  
 chuck.update();                       //check the wiichuck for new data
 
xJoy = chuck.readJoyX();              // puts the current value of the y (up-down) axis in the yJoy holder          
yJoy = chuck.readJoyY();              // puts the current value of the y (up-down) axis in the yJoy holder          

if (xJoy != xJoybase || yJoy != yJoybase) {
 //digitalWrite (row1,HIGH);
 //digitalWrite (row1,HIGH);
 //digitalWrite (row2,HIGH);
 //digitalWrite (row3,HIGH);
 digitalWrite (row4,HIGH);
 digitalWrite (row5,HIGH);
 digitalWrite (row6,HIGH);
 digitalWrite (row7,HIGH);
// digitalWrite (row8,HIGH);
// digitalWrite (column1,LOW);
// digitalWrite (column2,LOW);
// digitalWrite (column3,LOW);
// digitalWrite (column4,HIGH);
 digitalWrite (column5,LOW);
 digitalWrite (column6,LOW);
 digitalWrite (column7,LOW);
 digitalWrite (column8,LOW);



  
 // int positionx;                   // The mapped value
                                  // from 0 to 1023)
 // positionx = map(xJoy,0,1023,1,8); // percent will range from 0 to 100. 

//  int positiony;                   // The mapped value
                                  // from 0 to 1023)
//  positiony = map(yJoy,0,1023,1,8); // percent will range from 0 to 100. 

if (xJoy < 250){digitalWrite (column5, HIGH);}
    else if  (xJoy < 500){digitalWrite (column6, HIGH); }
     else if  (xJoy < 750){digitalWrite (column7, HIGH); }  
       else if  (xJoy >750){digitalWrite (column8, HIGH);  } 
//    else if  (positionx = 5){digitalWrite (column5, HIGH);  } 
 
  //  else if  (positionx = 6){digitalWrite (column6, HIGH);  } 
 //   else if  (positionx = 7){digitalWrite (column7, HIGH);  } 
 //   else if  (positionx = 8){digitalWrite (column8, HIGH); }
  
  if (yJoy < 250) {digitalWrite (row4, LOW);}  
  else if  (yJoy < 500){digitalWrite (row5, LOW);   }
  else if  (yJoy < 750){digitalWrite (row6, LOW);   }
  else if  (yJoy > 750){digitalWrite (row7, LOW);  } 
  //  else if  (positiony = 5){digitalWrite (row5, LOW);  } 
   // else if  (positiony = 6){digitalWrite (row6, LOW);  } 
   
  
 //   else if  (positiony = 7){digitalWrite (row7, LOW);  } 
  //  else if  (positiony = 8){digitalWrite (row8, LOW);  } 

     
     xJoybase = xJoy;
     yJoybase = yJoy;
     

delay(1);   
}}
