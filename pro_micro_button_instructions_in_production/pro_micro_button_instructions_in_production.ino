

#include <SPI.h>

const int buttonPin = 2;  // Set a button to any pin

int buttonState = 0;   
int duration = 0; 
    



// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval at which to blink (milliseconds)
unsigned long currentMillis = millis;
int tracker = 0;

void setup() {
  // set the digital pin as output:
  pinMode(buttonPin, INPUT);  // Set the button as an input

  
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if ((buttonState == HIGH) && (tracker==0))
{   currentMillis = millis();
    tracker = 1;
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
    Serial.println ("password sent");
    tracker=5;
  }
   
   if ((buttonState == LOW) && ((millis()- currentMillis) > 5000))  
    {
    Serial.println ("tap password timed out");
    tracker = 0;
    }
}
