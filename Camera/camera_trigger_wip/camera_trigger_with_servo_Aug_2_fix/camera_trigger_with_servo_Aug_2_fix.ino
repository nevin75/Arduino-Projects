#define SHUTTER_PIN 7

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
//int pos = 180 // code to pan the opposite way 
 
void setup() 
 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
  myservo.write(pos);      // move the servo to the originally assigned 'pos'
  delay (1000); // give the servo time to get set
  
}

void loop()
{
        for(pos = 0; pos < 180; pos +=5) // Starting at 0, until it gets to 180, the servo will increase the variable 'pos' by 5
       //for(pos = 180; pos>=1; pos-=5)  // code for the opposite direction
        myservo.write(pos);      // move the servo to the new position assigned in variable 'pos'
        delay (5000);  // wait 5 seconds
        digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
        delay(200); // hold the button down for .2 seconds
        digitalWrite(SHUTTER_PIN, LOW); //let off the shutter button
        delay (5000); //wait 5 seconds
  
  
 
      }



