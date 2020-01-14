/*
 POV

 1. define a message
 2. output vertical column of pixels and short delay
 3. repeat

*/
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

// pins to be used on Arduino for LCD display
int STR = A1;
int DOUT = A2;
int CLK = A0;

// the Qx in the order they are connected on the chip
int RS = 0x40;
int RW = 0x20;
int EnableSet = 0x10;
int EnableClr = 0xEF;
int DMASK = 0x0F;

// shift byte and strobe to display
void sendByteOut(int value)
{
 digitalWrite(STR,LOW);                     // set the strobe LOW
 shiftOut(DOUT, CLK, LSBFIRST, value);
shiftOut (DOUT, CLK, LSBFIRST, value);
digitalWrite(STR, HIGH);
 delayMicroseconds(100);
 digitalWrite(STR,LOW);
}

int* iMsg[] = {P,A,U,L};
int iMsgLen = 4;

// output tracking vars
int  iMsgIndex;
int  iCharIndex;
int  iCharLen;

void setup()
{
 pinMode(STR, OUTPUT);
 pinMode(DOUT, OUTPUT);
 pinMode(CLK, OUTPUT);

 iMsgIndex = 0;
 iCharIndex = 1;
 iCharLen = iMsg[iMsgIndex][0];
}

void loop()
{
 sendByteOut(iMsg[iMsgIndex][iCharIndex]);

 delay(3);

 iCharIndex++;
 if (iCharIndex == iCharLen)
 {
 iCharIndex = 1;
 iMsgIndex++;        // next letter
 }

 if (iMsgIndex == iMsgLen)
 {
 iMsgIndex = 0;
 }
 iCharLen = iMsg[iMsgIndex][0];

}
