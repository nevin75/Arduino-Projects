

//LED pins
const int Red = 9;
const int Green = 10;
const int Blue = 11;

//variables to store pin states.
int blueState = LOW;
int redState = LOW;
int greenState = LOW;

int incomingByte; // a variable to read incoming serial data into

void setup() {
// initialize serial communication:
Serial.begin(9600);
// initialize the LED pin as an output:
pinMode(Red, OUTPUT);
pinMode(Green, OUTPUT);
pinMode(Blue, OUTPUT);
}

void loop() {
// see if there's incoming serial data:
if (Serial.available() > 0) {

incomingByte = Serial.read();

//Parse serial data
if (incomingByte == 'r') {
if (redState == LOW) {
digitalWrite(Red, HIGH);
redState = HIGH;
}
else {
digitalWrite(Red, LOW);
redState = LOW;
}
}

if (incomingByte == 'g') {
if (greenState == LOW) {
digitalWrite(Green, HIGH);
greenState = HIGH;
}
else {
digitalWrite(Green, LOW);
greenState = LOW;
}
}

if (incomingByte == 'b') {
if (blueState == LOW) {
digitalWrite(Blue, HIGH);
blueState = HIGH;
}
else {
digitalWrite(Blue, LOW);
blueState = LOW;
}
}
}
}
