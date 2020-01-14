//**************************************************************//
//  Name    : shiftOutCode, Predefined Dual Array Style         //
//  Author  : Carlyn Maw, Tom Igoe                              //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = A1;
//Pin connected to SH_CP of 74HC595
int clockPin = A0;
////Pin connected to DS of 74HC595
int dataPin = A2;



int  A[] = { 8,
 0b11000000,
 0b01110000,
 0b00101100,
 0b00100110,
 0b00111000,
 0b11100000,
 0b10000000,
 0b00000000,
};
int  B[] = { 6,
 0b11111110,
 0b10010010,
 0b10010010,
 0b10010010,
 0b01111100,
 0b00000000,
};
int  C[] = { 8,
 0b00010000,
 0b01101100,
 0b10000010,
 0b10000010,
 0b10000010,
 0b11000110,
 0b01000100,
 0b00000000,
};
int  D[] = { 7,
 0b11111110,
 0b10000010,
 0b10000010,
 0b10000010,
 0b01000110,
 0b00111000,
 0b00000000,
};
int  E[] = { 6,
 0b11111110,
 0b10010010,
 0b10010010,
 0b10010010,
 0b10010010,
 0b00000000,
};
int  F[] = { 6,
 0b11111110,
 0b00010010,
 0b00010010,
 0b00010010,
 0b00000010,
 0b00000000,
};
int  G[] = { 8,
 0b00010000,
 0b01111100,
 0b10000010,
 0b10000010,
 0b10010010,
 0b10010010,
 0b01110100,
 0b00000000,
};
int  H[] = { 7,
 0b11111110,
 0b00010000,
 0b00010000,
 0b00010000,
 0b11111110,
 0b11111110,
 0b00000000,
};
int  I[] = { 2,
 0b11111110,
 0b00000000,
};
int  J[] = { 5,
 0b01000000,
 0b10000000,
 0b10000000,
 0b11111110,
 0b00000000,
};
int  K[] = { 7,
 0b11111110,
 0b00010000,
 0b00011000,
 0b00100100,
 0b11000010,
 0b10000000,
 0b00000000,
};
int  L[] = { 5,
 0b11111110,
 0b10000000,
 0b10000000,
 0b10000000,
 0b00000000,
};
int  M[] = { 8,
 0b11111110,
 0b00011100,
 0b11100000,
 0b11000000,
 0b00111000,
 0b00011110,
 0b11111110,
 0b00000000,
};
int  N[] = { 7,
 0b11111110,
 0b00001100,
 0b00011000,
 0b01100000,
 0b11111110,
 0b11111110,
 0b00000000,
};
int  O[] = { 8,
 0b00010000,
 0b01101100,
 0b10000010,
 0b10000010,
 0b10000010,
 0b11000110,
 0b01111100,
 0b00000000,
};
int  P[] = { 6,
 0b11111110,
 0b00010010,
 0b00010010,
 0b00010010,
 0b00011110,
 0b00000000,
};
int  Q[] = { 9,
 0b00111000,
 0b01101100,
 0b10000010,
 0b10000010,
 0b11000010,
 0b11000110,
 0b11111100,
 0b10000000,
 0b00000000,
};
int  R[] = { 7,
 0b11111110,
 0b00010010,
 0b00010010,
 0b00110010,
 0b11011110,
 0b10000000,
 0b00000000,
};
int  S[] = { 7,
 0b01000000,
 0b11001110,
 0b10010010,
 0b10010010,
 0b10010010,
 0b01100100,
 0b00000000,
};
int  T[] = { 7,
 0b00000010,
 0b00000010,
 0b00000010,
 0b11111110,
 0b00000010,
 0b00000010,
 0b00000000,
};
int  U[] = { 7,
 0b01111110,
 0b10000000,
 0b10000000,
 0b10000000,
 0b11111110,
 0b00111110,
 0b00000000,
};
int  V[] = { 8,
 0b00000010,
 0b00011100,
 0b01100000,
 0b11000000,
 0b00110000,
 0b00001110,
 0b00000010,
 0b00000000,
};
int  W[] = { 11,
 0b00000110,
 0b00111100,
 0b11100000,
 0b11110000,
 0b00001110,
 0b00001110,
 0b11110000,
 0b11100000,
 0b00111110,
 0b00000010,
 0b00000000,
};
int  X[] = { 7,
 0b10000010,
 0b01000110,
 0b00101100,
 0b00111000,
 0b01100100,
 0b11000010,
 0b00000000,
};
int  Y[] = { 7,
 0b00000010,
 0b00000100,
 0b00011000,
 0b11110000,
 0b00001100,
 0b00000010,
 0b00000000,
};
int  Z[] = { 7,
 0b10000000,
 0b11100010,
 0b10110010,
 0b10011010,
 0b10000110,
 0b10000010,
 0b00000000,
};

//holders for infromation you're going to pass to shifting function
byte dataCathode;
byte dataAnode;
byte dataArrayCathode[10];
byte dataArrayAnode[10];

int text[] = {N,E,V,I,N};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  Serial.begin(9600);

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayCathode[0] = 0x00; //0xFF; //11111111
  dataArrayCathode[1] = 0x00; //0xFE; //11111110
  dataArrayCathode[2] = 0x00; //0xFC; //11111100
  dataArrayCathode[3] = 0x00; //0xF8; //11111000
  dataArrayCathode[4] = 0x00; //0xF0; //11110000
  dataArrayCathode[5] = 0x00; //0xE0; //11100000
  dataArrayCathode[6] = 0x00; //0xC0; //11000000
  dataArrayCathode[7] = 0x00; //0x80; //10000000
  dataArrayCathode[8] = 0x00; //00000000
  dataArrayCathode[9] = 0x00; //0xE0; //11100000

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayAnode[0] = 0xFF; //11111111
  dataArrayAnode[1] = 0x7F; //01111111
  dataArrayAnode[2] = 0x3F; //00111111
  dataArrayAnode[3] = 0x1F; //00011111
  dataArrayAnode[4] = 0x0F; //00001111
  dataArrayAnode[5] = 0xFF; //0x00; //0x07; //00000111
  dataArrayAnode[6] = 0xFF; //0x00; //0x03; //00000011
  dataArrayAnode[7] = 0xFF; //0x00; //0x01; //00000001
  dataArrayAnode[8] = 0xFF; //0x00; //0x00; //00000000
  dataArrayAnode[9] = 0xFF; //0x00; //0x07; //00000111

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  blinkAll_2Bytes(8000,5000); 
}

void loop() {

for (int m = 0; m<4, m++) {

  for (int j = 0; j < 8; j++) {
    //load the light sequence you want from array
    dataAnode = (0x01 << m);
    dataCathode = (text[m])[j];
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //move 'em out
    shiftOut(dataPin, clockPin, dataCathode);   
    shiftOut(dataPin, clockPin, dataAnode);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
    delay(300);
  }
}



// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}


//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(200);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}

