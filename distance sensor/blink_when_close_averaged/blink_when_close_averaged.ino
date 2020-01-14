// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

int led = 13;
int dist = 0;
int distgroup = 0;
int count = 0;
int user = 0;

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 300 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() {
    pinMode(led, OUTPUT);   
}

void loop() {
  count = (count+1);
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  dist = sonar.ping();
  distgroup = (distgroup + dist);
  while (count >= 100) {
     if (distgroup < 150450) {user = 1;}
     else {user = 0;}}
    
 if (count >= 100) {
    count = 0;
    distgroup = 0;}
    
  while (user = 1) {digitalWrite(led,HIGH); delay(50);digitalWrite(led,LOW); delay (50);};
  while (user = 0) {digitalWrite(led,HIGH); delay(1000); digitalWrite(led,LOW); delay(1500);}}


