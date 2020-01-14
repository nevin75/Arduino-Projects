// Maurice Ribble
// 4-28-2008
// http://www.glacialwanderer.com/hobbyrobotics




#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 

 
//#define FOCUS_PIN 6
#define SHUTTER_PIN 7


{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

  //pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  //digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  
}

void loop()
{
         digitalWrite(SHUTTER_PIN, HIGH);
        delay(200); // May want to adjust this depending on shot type
        digitalWrite(SHUTTER_PIN, LOW);
  
  for(pos = 0; pos < 180; pos +=5) myservo.write(pos);              // tell servo to go to position in variable 'pos' 
  //  delay(15);                      // waits 15ms for the servo to reach the position 
//}

for(pos = 180; pos>=1; pos-=5) myservo.write(pos);      // goes from 180 degrees to 0 degrees 
                                  
                                 // waits 15ms for the servo to reach the position 
  
  
 delay(1000);  
      }



