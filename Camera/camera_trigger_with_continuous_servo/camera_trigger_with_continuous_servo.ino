#define SHUTTER_PIN 7

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 

//int pos = 0;    // variable to store the servo position 
int pos = 87

; // code to pan the opposite way 
 
void setup() 
 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
  myservo.write(pos);      // move the servo to the originally assigned 'pos'
 // delay (1000); // give the servo time to get set
  
}

void loop()
{
     //   if (pos < 180){
            digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
           delay(200); // hold the button down for .2 seconds
            digitalWrite(SHUTTER_PIN, LOW); //let off the shutter button
            delay (5000); //wait 5 seconds
         //   pos = (pos + 10); // Increase the position variable by 5
         //   myservo.write(pos);      // move the servo to the new position assigned in variable 'pos'
         //   delay (20000); } // wait 5 seconds 
     //  else 
      //     { digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
      //      delay(200); // hold the button down for .2 seconds
      //      digitalWrite(SHUTTER_PIN, LOW);} //let off the shutter button 
       
    }



