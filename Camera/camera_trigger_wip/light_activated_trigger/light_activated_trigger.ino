#define SHUTTER_PIN 7

 
 int LDR_Pin = A0; //analog pin 0

void setup() 
 
{ 
  pinMode(SHUTTER_PIN, OUTPUT);
  digitalWrite(SHUTTER_PIN, LOW);
   Serial.begin(9600);     
}

void loop()
{   int LDRReading = analogRead(LDR_Pin); 
 Serial.println(LDRReading);
    
      if(LDRReading>680)
        {
            digitalWrite(SHUTTER_PIN, HIGH); //trigger the camera
           delay(200); // hold the button down for .2 seconds
           digitalWrite(SHUTTER_PIN, LOW); //let off the shutter button
           } // wait 5 seconds 
      
       
   }



