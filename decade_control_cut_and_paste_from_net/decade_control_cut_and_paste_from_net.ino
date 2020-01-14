

/*5 LED sequential flasher based on 4017 decade counter.*/

//Define pins to be used.
int clockPin = 9;
int enablePin = 10;

void setup()
{
  //Set pins 9 & 10 as output.
  pinMode(clockPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop()
/*Check current state of pins, change to oposite of 
  current value. */
{
  delay(1000);
  if (clockPin == HIGH);
  {
    digitalWrite(clockPin, LOW);
    digitalWrite(enablePin, HIGH);
  }
  if (clockPin == LOW);
  {
    digitalWrite(clockPin, HIGH);
    digitalWrite(enablePin, LOW);
  }
}
