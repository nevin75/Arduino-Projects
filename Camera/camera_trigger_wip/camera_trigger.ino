// Maurice Ribble
// 4-28-2008
// http://www.glacialwanderer.com/hobbyrobotics

// This code just tests my camera trigger.  It lets you
// focus the camera by pressing the 'f' key and take a
// picture by pressing the space bar.

#define FOCUS_PIN 6
#define SHUTTER_PIN 7

void setup()
{
  pinMode(FOCUS_PIN, OUTPUT);
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
  digitalWrite(SHUTTER_PIN, LOW);
  
}

void loop()
{
         digitalWrite(SHUTTER_PIN, HIGH);
        delay(2000); // May want to adjust this depending on shot type
        digitalWrite(SHUTTER_PIN, LOW);
        delay(10000);
      }



