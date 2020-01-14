#define SHUTTER_PIN 7

#include <Servo.h> 
#include <LiquidCrystal.h>
#include <DFR_Key.h>

//Pin assignments for SainSmart LCD Keypad Shield
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 


DFR_Key keypad;
 
int localKey = 0;
String keyString = "";
 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
//int pos = 180 // code to pan the opposite way 
 
void setup() 
 { 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R for Clockwise");
  lcd.setCursor (1, 0);
  lcd.print("L for Counter-clockwise");
  
  {if keypad.get(key) = 5;
  int pos = 0; }
  
    {if keypad.get(key) = 2;
  int pos = 180; }
  
  /*
  OPTIONAL
  keypad.setRate(x);
  Sets the sample rate at once every x milliseconds.
  Default: 10ms
  */
  keypad.setRate(10);

}
 
 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
  myservo.write(pos);      // move the servo to the originally assigned 'pos'
  delay (1000); // give the servo time to get set
  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time Lapse Setup");
  delay(2500);
  
  
}

void loop()
{
        if (pos < 180){
            digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
            delay(200); // hold the button down for .2 seconds
            digitalWrite(SHUTTER_PIN, LOW); //let off the shutter button
            delay (5000); //wait 5 seconds
            pos = (pos + 5); // Increase the position variable by 5
            myservo.write(pos);      // move the servo to the new position assigned in variable 'pos'
            delay (5000); } // wait 5 seconds 
       else 
           { digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
            delay(200); // hold the button down for .2 seconds
            digitalWrite(SHUTTER_PIN, LOW);} //let off the shutter button 
       
   }



