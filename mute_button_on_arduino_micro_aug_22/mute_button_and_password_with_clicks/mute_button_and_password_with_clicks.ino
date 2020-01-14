#include <Keyboard.h>
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

unsigned long currentMillis = millis;
int tracker = 0;

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  
}

void loop()
{

    
  buttonState = digitalRead(buttonPin);

  
  if ((buttonState == HIGH) && (tracker==0) /*&& (currentMillis > 500)*/)
{   currentMillis = millis();
    tracker = 1; 
    Keyboard.press('z');
    Keyboard.press('x');
    Keyboard.releaseAll();
    delay (50);
    }

if ((buttonState == LOW) && ((millis() - currentMillis) < 200) && (tracker==1))
  {tracker = 2;
  }

if ((buttonState == HIGH) && ((millis() - currentMillis) < 300) && (tracker==2))
  {tracker = 3;
  }

  if ((buttonState == LOW) && ((millis() - currentMillis) < 400) && (tracker==3))
  {tracker = 4;
  }

  if ((buttonState == HIGH) && ((millis() - currentMillis) > 2000) && (tracker==4))
  {    
    Keyboard.println("Wicket35");
    tracker=5;
  }
   
   if ((buttonState == LOW) && ((millis()- currentMillis) > 2500))   
    {
    tracker = 0;
    }
}
