// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
int led = 13;
int led2 = 10;
int reading1;

int reading2;
int reading3;
int reading4;
int total;
/*
int reading5;
*/

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(led, OUTPUT);
  pinMode (led2, OUTPUT);  
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  unsigned int uS = sonar.ping_median(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
 
reading1 = (uS /US_ROUNDTRIP_CM);
delay (50);
reading2 = (uS/US_ROUNDTRIP_CM);
delay (50);
reading3 = (uS/US_ROUNDTRIP_CM);
delay (50);
reading4 = (uS/US_ROUNDTRIP_CM);

total = (reading1 + reading2 + reading3 + reading4);


//if (reading1 < 100 && reading1 > 10) || reading2 < 100 && reading2 > 10 || reading3 < 100 && reading3 > 10 || reading4 < 100 && reading4 > 10) //& reading3 < 100 && reading3 > 10 || reading1 < 100 && reading1 > 10 && reading4 < 100 && reading4 > 10 || reading2 < 100 && reading2 > 10 && reading4 < 100 && reading4 > 10 || reading3 < 100 && reading3 > 10 && reading4 < 100 && reading4 > 10 || reading1 < 100 && reading1 > 10 && reading5 < 100 && reading5 > 10 || reading2 < 100 && reading2 > 10 && reading5 < 100 && reading5 > 10 || reading3 < 100 && reading3 > 10 && reading5 < 100 && reading5 > 10 || reading4 < 100 && reading4 > 10 && reading5 < 100 && reading5 > 10  ) 
 if (total > 100 && total < 300) 
     {
       digitalWrite(led,HIGH); 
       digitalWrite(led2,HIGH);
     }       
 /*     else 
       {if (reading1 = 0)
         {
         reading1 = (uS /US_ROUNDTRIP_CM);
         delay (100);
         reading1 = reading1 + (uS /US_ROUNDTRIP_CM);
       //  delay (100);
       //  reading1 = reading1 + (uS /US_ROUNDTRIP_CM);
       //  delay (100);
       //  reading1 = reading1 + (uS /US_ROUNDTRIP_CM);
      //   delay (100);
      //   reading1 = reading1 + (uS /US_ROUNDTRIP_CM);
           if (reading1 > 20)
             {
               digitalWrite(led,HIGH); 
               digitalWrite(led2,HIGH);
             }
         }    
   */   
     else
      {
       digitalWrite(led,LOW); 
       digitalWrite(led2,LOW);
      }
    }  

  
 /*if (reading1 < 100 && reading1 > 10)
  
{
  reading5 = reading4;
  reading4 = reading3;
  reading3 = reading2;
  reading2 = reading1;}
  else {
  reading5 = reading4;
  reading4 = reading3;
  reading3 = reading2;
  reading2 = 0;}
     }*/
  
  

/*
 
 if (((uS / US_ROUNDTRIP_CM) > 2)  && ((uS / US_ROUNDTRIP_CM) < 110))
     {
       digitalWrite(led,HIGH); 
       digitalWrite(led2,HIGH);
     }       
    else 
     {
       digitalWrite(led,LOW); 
       digitalWrite(led2,LOW);
     }
   */ 

