#include <Wire.h>
#include <Keyboard.h>
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input
  Wire.begin();        // join i2c bus (address optional for master)
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
  
  
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character

  if (c=="Y")
    {Keyboard.println("Wicket35");;
    delay(100);
    Keyboard.println("Wicket35");
    delay (1000);
    }
 }

  delay(500);
}


