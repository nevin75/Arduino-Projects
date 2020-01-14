/*
  Intervalometer
  Takes a picture every 10 seconds, repeatedly.
 
 */
 
// Pin 9 is connected to a relay that closes the shutter trigger loop.
// give it a name:
int shutter = 9;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(shutter, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(shutter, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(50);               // wait for 50 milliseconds
  digitalWrite(shutter, LOW);    // turn the LED off by making the voltage LOW
  delay(10000);               // wait for 10 seconds
}
