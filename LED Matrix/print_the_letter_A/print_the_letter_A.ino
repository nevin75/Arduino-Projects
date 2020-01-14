
#define latchPin A1
#define clockPin A0
#define dataPin A2

byte anodedatatosend;
byte cathodedatatosend;
byte theletterA[8] =  {0, 31, 36, 68, 36, 31, 0, 255};
//byte theletterA[8] =  {1,1,1,1,1,1,1,1};
byte groundrow[8] = {254, 253, 251, 248, 239, 223, 189, 127};
//byte groundrow[8] = {127,127,127,127,127,127,127,127};
int i = 0;

void setup() 
  {
  //set pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}


void loop() {  
 // put your main code here, to run repeatedly:


    for (i=0;i<8;i++){
      byte cathoddedatatosend = groundrow[i];  //ground one of the rows
        //while that row is grounded, feed in the relevant anode hits in the series
      byte anodedatatosend = theletterA[i];
     //hold the register output while we send information
        digitalWrite(latchPin, LOW);
    
//    shift out the bits of cathode and anode dataToSend to the 74HC595
       shiftOut(dataPin, clockPin, MSBFIRST, anodedatatosend);
       shiftOut(dataPin, clockPin, MSBFIRST, cathodedatatosend);
  
     
    //set latch pin high- this sends data to outputs so the LEDs will light up
    digitalWrite(latchPin, HIGH);
    delay (10);
    }
}

