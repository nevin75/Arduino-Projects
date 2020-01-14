/*
Read multiple IR sensors and report on Serial Print
Created By: Nevin
Created On: 2015-10-11

*/
int Sensor_Pin0 = A0;
int Sensor_Pin1 = A1;
int Sensor_Pin2 = A2;
int Sensor_Pin3 = A3;
int Sensor_Pin4 = A4;

void setup()
{
 
  Serial.begin(9600);

//    pinMode(6,OUTPUT);
}
void loop()
{
{
   int SensorReading[5];
   int SensorPins[] = {Sensor_Pin0, Sensor_Pin1, Sensor_Pin2, Sensor_Pin3, Sensor_Pin4};
   for(int i=0;i<5;i++)    //Output a frequency of sound
        {
          SensorReading[i] = analogRead(SensorPins[i]);
         Serial.print (i);
        Serial.print (": ");
         Serial.println(SensorReading[i]);
  //       if ( SensorReading[0] < 3 )
  //       {Serial.println("Up Up");}
  //        if (SensorReading[1] < 3 )
  //       {Serial.println("Up");}
  //         if (SensorReading[2] < 3 )
  //       {Serial.println("Middle");}
  //         if (SensorReading[3] < 3 )
  //       {Serial.println("Down");}
 //          if (SensorReading[4] < 3) 
 //        {Serial.println("Down Down");}
        
        }
        delay (1000);
        
  }
}
