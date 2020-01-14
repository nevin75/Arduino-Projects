#include <Keyboard.h>
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  
}

void loop()
{

    
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) 
  {
    Keyboard.press('z');
    Keyboard.press('x');
    delay(50);
    Keyboard.releaseAll();
    delay (1000);
  }
   else {
    }
}
