/*
  Intervalometer
  Takes a picture every 10 seconds, repeatedly.
 
 */
 // variable to hold sensor value
int sensorValue;

int ledPin = 12;
// Pin 9 is connected to a relay that closes the shutter trigger loop.
// give it a name:
int shutter = 9;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;
// the setup routine runs once when you press reset:
void setup() 
{    pinMode(ledPin, OUTPUT); 
digitalWrite (ledPin, HIGH);

 while (millis() < 5000) 
  {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) 
      {
      sensorHigh = sensorValue;
      }
    // record the minimum sensor value
    if (sensorValue < sensorLow) 
      {
      sensorLow = sensorValue;
      }
   }
 }
 
 
// the loop routine runs over and over again forever:
void loop() 
{
  sensorValue = analogRead(A0);
  
  if (sensorValue > sensorHigh)
  
   {
    digitalWrite (ledPin, HIGH);
    digitalWrite(shutter, HIGH);   // turn the transistor on (HIGH is the voltage level)
    delay(50);               // keep the circuit closed for 50 milliseconds
    digitalWrite(shutter, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite (ledPin,HIGH);
    delay(10);               // wait for 10 seconds
   }
 }
