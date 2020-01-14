
/* Analog Input
* Demonstrates analog input by reading an analog sensor on analog
* pin 0 and turning on and off a light emitting diode(LED) connected to
digital pin 13.
* The amount of time the LED will be on and off depends on the value obtained by
* analogRead().
* Created by David Cuartielles
* Modified 16 Jun 2009
* By Tom Igoe
* http://arduino.cc/en/Tutorial/AnalogInput
*/
int sensorPin = 0; // select the input pin for the potentiometer
int ledPin = 13; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() {
  pinMode(ledPin, OUTPUT); //declare the ledPin as an OUTPUT:
}
void loop() {
  sensorValue = analogRead(sensorPin);// read the value from the sensor:
  digitalWrite(ledPin, HIGH); // turn the ledPin on
  delay(sensorValue); // stop the program for <sensorValue> milliseconds:
  digitalWrite(ledPin, LOW); // turn the ledPin off:
  delay(sensorValue); // stop the program for for <sensorValue> milliseconds:
}


