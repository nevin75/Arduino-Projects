/*
  Intervalometer
  Takes a picture every 10 seconds, repeatedly.
 
 */
 
// Pin 9 is connected to a relay that closes the shutter trigger loop.
// give it a name:
    int shutter = 9;

//Pin 10 is connected to a transistor that releases enough voltage to trigger 
//the single throw, double pole resistor, which in turn triggers voltage for the motor.
    int motor = 10;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
    pinMode(shutter, OUTPUT);     
  }

// the loop routine runs over and over again forever:
void loop() {
//trigger the camera
  digitalWrite(shutter, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(50);               // wait for 50 milliseconds
   digitalWrite(shutter, LOW);    // turn the LED off by making the voltage LOW

// wait 2 seconds
  delay(2000);               // wait for 2 seconds
  
// trigger the transistor/relay/motor series, hopefully with limited voltage
  digitalWrite(motor, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(50);               // wait for 50 milliseconds
   digitalWrite(motor, LOW);    // turn the LED off by making the voltage LOW

  
//wait 10 seconds before starting cycle again
  delay (10000);
 
  }
