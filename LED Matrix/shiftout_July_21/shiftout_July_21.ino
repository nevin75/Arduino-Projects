
//**************************************************************//
//  Name    : shiftOutCode, Hello World                         //
//  Author  : Carlyn Maw,Tom Igoe                               //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

#define BIT8 ~0x01
#define BIT7 ~0x02
#define BIT6 ~0x04
#define BIT5 ~0x08
#define BIT4 ~0x10
#define BIT3 ~0x20
#define BIT2 ~0x40
#define BIT1 ~0x80



//eightBits &= (bits[3] & bits[4]);
//Alternatively, if you can use C++, you could just use an std::vector<bool> which is internally defined as a vector of bits, complete with direct indexing.}
//Pin connected to ST_CP of 74HC595
// */int latchPin = 8;
//Pin connected to SH_CP of 74HC595
//int clockPin = 12;
////Pin connected to DS of 74HC595
//int dataPin = 11;
//Pin connected to ST_CP of 74HC595
int latchPin = A1;
//Pin connected to SH_CP of 74HC595
int clockPin = A0;
//Pin connected to DS of 74HC595
int dataPin = A2;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  char bits[8] = {BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8};

}

void loop() {
 
  //count up routine
  for (int j = 0; j < 8; j++) {
    
   for (int x=0; x < 256; x++) {
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, bits[j]);   
    shiftOut (dataPin, clockPin, LSBFIRST, x);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
} 
 

