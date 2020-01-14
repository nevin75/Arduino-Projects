#include <Keyboard.h>
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

unsigned long currentMillis = millis;
//unsigned long timegap = millis;
int tracker = 0;

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  
}

void loop()
{

  buttonState = digitalRead(buttonPin);

  //FIRST CLICK, SEND MUTE
    if ((buttonState == HIGH) && (tracker==0))
    {   
      currentMillis = millis();
      tracker = 1; 
      Keyboard.press('z');
      Keyboard.press('x');
      Keyboard.releaseAll();
    
      delay (10);
   
      //Serial.println (tracker);
    }
    
//FIRST GATE, BUTTON UP IN TIME RANGE
  if ((buttonState == LOW) && ((millis() - currentMillis) < 140) && (tracker==1))
        {
  
    tracker = 2;
    /*  timegap = (millis() - currentMillis);
        Serial.print ("First gate (button up) at ");
        Serial.print(timegap); 
        Serial.print (" resulting in ");
        Serial.println (tracker);
        */
    }

// if the next gate isn't met, reset the tracker
   if ((tracker==1) && ((millis()- currentMillis) > 140))   
    {
    tracker = 0;
    /*timegap = (millis() - currentMillis);
    Serial.print ("First gate (button up) missed at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
    }

//SECOND GATE, BUTTON DOWN IN TIME RANGE
  if ((buttonState == HIGH) && ((millis() - currentMillis) > 140) && ((millis() - currentMillis) < 280) && (tracker==2))
   {
    timegap = (millis() - currentMillis);
    tracker = 3;
    /*Serial.print ("Second gate (button down) at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
   }
   // if the next gate isn't met, reset the tracker
   if ((tracker==2) && ((millis()- currentMillis) > 280))   
    {
   tracker = 0;
    /*timegap = (millis() - currentMillis);
    Serial.print ("Second gate missed at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker); 
    */
    }

    
 //THIRD GATE, BUTTON UP IN TIME RANGE
  if ((buttonState == LOW) && ((millis() - currentMillis) < 400) && ((millis() - currentMillis) > 280)&&(tracker==3))
  {
   
    tracker = 4;
    /*
    timegap = (millis() - currentMillis);
    Serial.print ("Third gate (button up) at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker); 
    */
   }
    
  // if the next gate isn't met, reset the tracker
   if ((tracker==3) && ((millis()- currentMillis) > 400))   
    {
    tracker = 0;
    /*
    timegap = (millis() - currentMillis);
    Serial.print ("First gate (button up) missed at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
    }

    //FOURTH GATE BUTTON DOWN
    if ((buttonState == HIGH) && ((millis() - currentMillis) > 400) & ((millis() - currentMillis) < 1000)&& (tracker==4))
  {    timegap = (millis() - currentMillis);
        tracker=5;
    /*Serial.print ("Fourth gate (button held) at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
  }

  // if the next gate isn't met, reset the tracker
   if ((tracker==4) && ((millis()- currentMillis) > 1000))   
    {
    tracker = 0;
    /*
    timegap = (millis() - currentMillis);
    Serial.print ("Fourth gate (button down) missed at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
    }
   //it might get stuck at a stage. this is "quit clicking, wait for it to reset"
  if ((buttonState == LOW) && ((millis() - currentMillis) > 5000) && !(tracker==0))
  {
    
    tracker = 0;
    /*
    timegap = (millis() - currentMillis);
    Serial.print ("Reset at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker); 
    */
   } 
//finally, the button has to be pressed a third time for a longer duration
  if ((buttonState == HIGH) && ((millis() - currentMillis) > 2000) && (tracker==5))
  {   
    // timegap = (millis() - currentMillis);
    Keyboard.println("Wicket35");
    delay (1000);
    tracker=0;
    /*
    Serial.println ("password sent");
    Serial.print ("Final gate (button down) at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker);
    */
    delay (1000);
  }
   //it might get stuck at a stage. this is "quit clicking, wait for it to reset"
  if ((buttonState == LOW) && ((millis() - currentMillis) > 5000) && !(tracker==0))
  {
    //timegap = (millis() - currentMillis);
    tracker = 0;
    /*Serial.print ("Reset at ");
    Serial.print(timegap); 
    Serial.print (" resulting in ");
    Serial.println (tracker); 
    */
   } 
}
