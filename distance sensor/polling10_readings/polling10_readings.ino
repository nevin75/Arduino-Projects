/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 13 Trig to Arduino pin 12
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPin 12
#define echoPin 11
#define led 13
#define led2 10

int distance1 = 0;
int distance2 = 0;
int distance3 = 0;
int distance4 = 0;
int distance5 = 0;
int distance6 = 0;
int distance7 = 0;
int distance8 = 0;
int distance9 = 0;
int distance10 = 0;
int MAX = 120;
int polling;
int visitor;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {

 
  //MEASURE DISTANCE USING HC-SR04
  long duration, distance;
 digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH, 10000);
  distance = (duration/2) / 29.1;
  

//RESET POLLING  
  polling = 0;

// ADVANCE POLLING NUMBERS FOR THIS CYCLE
    
  distance10 = distance9;
 // AND TEST IF IT CONTRIBUTES TO THE POLLING TOTAL
 if (distance10 > 10 && distance10 < MAX)
   {polling = polling + 1;}
 
  distance9 = distance8;
 if (distance9 > 10 && distance9 < MAX)
    {polling = polling + 1;}
 
  distance8 = distance7;
 if (distance8 > 10 && distance8 < MAX)
    {polling = polling + 1;} 
    
    distance7 = distance6;
 if (distance7 > 10 && distance7 < MAX)
    {polling = polling + 1;}
    
     distance6 = distance5;
 if (distance6 > 10 && distance6 < MAX)
    {polling = polling + 1;}
    
     distance5 = distance4;
 if (distance5 > 10 && distance5 < MAX)
    {polling = polling + 1;}
    
     distance4 = distance3;
 if (distance4 > 10 && distance4 < MAX)
    {polling = polling + 1;}
    
     distance3 = distance2;
 if (distance3 > 10 && distance3 < MAX)
    {polling = polling + 1;}
    
     distance2 = distance1;
 if (distance2 > 10 && distance2 < MAX)
    {polling = polling + 1;}
    
    distance1 = distance;
 if (distance1 > 10 && distance1 < MAX)
   {polling = (polling + 1);}
   
// TEST POLLING TO DETERMINE IF SOMEONE IS THERE

// if (polling > 5) {visitor = 1;}
 
 //if (polling <= 5) {visitor = 0;}

// LIGHT OR NOT

 if (polling > 3) {  
   digitalWrite(led,HIGH);
   digitalWrite(led2,HIGH);}

//if (visitor = 0)
else {
   digitalWrite(led,LOW);
   digitalWrite(led2,LOW);}
 
 //REPORT TO SERIAL MONITOR
    Serial.print(distance);
    Serial.println(" cm  ");
  
  delay(200);
}
