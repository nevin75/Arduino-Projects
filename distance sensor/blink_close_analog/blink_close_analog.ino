
#include <NewPing.h>

int led = 13;
int dist = 0;
int user = 0;
int constant = 8;

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() 
  {
    pinMode(led, OUTPUT);   
  }

void loop() 
  {
    delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    dist = sonar.ping();
    //if (99 < dist < 100) 
  /*  if (constant = 7)
         {
           user = 1;
         }
      else 
         {
           user = 0;
         }           
    
    while (user = 1)
        {
           digitalWrite(led,HIGH); 
              delay(50);
           digitalWrite(led,LOW); 
             delay (50);
        };
    while (user = 0)
        {
          digitalWrite(led,HIGH); 
            delay(1500); 
          digitalWrite(led,LOW); 
            delay(500);
   */
  analogWrite(led, dist);
   }
     


