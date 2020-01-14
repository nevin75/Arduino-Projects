/*
 * "ArduinomeFirmware" - Arduino Based Monome Clone by Owen Vallis & Jordan Hochenbaum 06/16/2008
 * Revised 06/26/2008
 * Revised 07/20/2008 by Ben Southall
 * Revised 03/21/2009 Ben Southall
 * Revised 01/21/2012 Jordan Hochenbaum v3.3 rev.a
 * Revised 06/2012 for 74HC595 by Amanda Ghassaei
 * --------------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * --------------------------------------------------------------------------
 *
 * This code is largely a direct translation of the 40h protocol designed by Brian Crabtree
 * & Joe Lake, and coded by Joe Lake.  We would like to express our utmost thanks for making
 * the monome & its inner-workings available and open source.  We would also like to extend
 * our thanks to all those who have helped us get this far in successfully making an arduino-
 * based monome clone, including but not limited to Brad Hill for his awesome arduino shield, 
 * and Melka for showing how to pack and unpack the serial data.
 *
 * Additional comment and attribution 7/20/2008 : 
 * The changes on 7/20/2008 were inspired by, and at least in some part, directly
 * copied from the 'Octinct' code written by Jonathan M Guberman (upwardnotnorthward.com).  
 * In particular, the use of timer 2 to drive an interrupt routine to read the serial port was
 * picked up from the Octinct project, and also, setting the baud rate to 57600 seemed to be 
 * critical for getting everything to work reliably.  My thanks to Jonathan for sharing his
 * software, and for figuring out how to keep that serial buffer in check.
 *
 * Changes 03/21/2009
 *
 * Added ADC support for arduino ADCs 0 - 3.  Thanks to Josh Lory for the first cut of the code for
 * this.  Added handling of the ADC enable/disable serial messages, and changed Josh's checkADC code
 * to loop through the 4 ADCs rather than read each one individually.  Also, cleaned up a number of
 * unused variables, and moved all PORT/pin definitions to the top of the file; this should make it
 * easier for people not using the unsped shield to change the hardware connections.
 * 
 * Please DO NOT email monome with technical questions and/or help regarding this code or clone.  
 * They are in NO WAY responsible or affiliated with this project other than they were our inspiration 
 * and we used many of their methods and pulled from their code.
 * 
 * Additionally, while we are availble and willing to help as much as possible, we too CANNOT be held
 * responsible for anything you do with this code.  Please feel free to report any bugs, suggestions 
 * or improvements to us as they are all welcome.  Again, we cannot be held responsible for any damages 
 * or harm caused by the use or misuse of this code or our instructions.  Thank you for understanding.
 *
 *
 *
 *
 * Changes 01/21/2012 & 3.3a
 * Arduino 1.0+ compatability (uses .ino extension and no longer specifies BYTE type in Serial.write)
 * --------------------------------------------------------------------------
 *
 * Links:
 *  www.monome.org  - Our website - Click "Work/Arduinome" on the Navigation Menu on the top.
 *  www.monome.org  - the "original" monome and our inspiration
 *  www.monome.org 
 *  www.monome.org 
 *
 */

// PIN and PORT assignments
// If you're using hardware other than the unsped shield, you'll want to go through this portion of the code, 
// and change the pin numbers and atmega 168 PORTs that you're using.  We're using pin/PORT assignments here, 
// NOT the pin number scheme from the arduino board outputs (e.g. arduino digital pin 8 = PORTB pin 1)
// However, in the comments below, I do give the equivalents between arduino digital pin numbers and the 
// atmega168's PORT/bit numbering.

// IMPORTANT - you'll need to make sure that you set the data following two direction register variables to match your
// pin assignments.
byte PORTD_Data_Direction = 0x02;//all inputs except pin 1 (TX)
byte PORTB_Data_Direction = 0xFF;//all outputs
byte PORTC_Data_Direction = 0xFC;//A2-A5 are outputs, A0, A1 inputs

//Connections to 595 shift register
//dataPin = A4 = PORTC, bit 4
//clockPin = A2 = PORTC, bit 2
//latchPin = A3 = PORTC, bit 3
#define DATA_PORT_595 (PORTC)
byte dataPin595 = 4;
byte dataPin595MaskHigh = 1 << dataPin595;
byte dataPin595MaskLow = ~dataPin595MaskHigh;

#define CLOCK_PORT_595 (PORTC)
byte clockPin595 = 2;
byte clockPin595MaskHigh = 1 << clockPin595;
byte clockPin595MaskLow = ~clockPin595MaskHigh;

#define LATCH_PORT_595 (PORTC)
byte latchPin595 = 3;
byte latchPin595MaskHigh = 1 << latchPin595;
byte latchPin595MaskLow = ~latchPin595MaskHigh;

// Connections to the Max7219 (drives LEDS)
// dataIn = arduino pin A5 = PORTC, bit 5
// load = arduino pin 11 = PORTB bit 4
// clock = arduino pin 12 = PORTB, bit 5
#define LED_DATA_PORT (PORTC)
byte MaxDataPin = 5;
byte DataMaskHigh = 1 << MaxDataPin;
byte DataMaskLow = ~DataMaskHigh;

#define LED_CLOCK_PORT (PORTB)
byte MaxClockPin = 5;
byte ClockMaskHigh = 1<<MaxClockPin;
byte ClockMaskLow = ~ClockMaskHigh;

#define LED_LOAD_PORT (PORTB)
byte MaxLoadPin = 4;
byte LoadMaskHigh = 1 << MaxLoadPin;
byte LoadMaskLow = ~LoadMaskHigh;
// end connections to the 165 shift register

//use this to fix mirroring
boolean mirrorXLEDs = true;
boolean mirrorYLEDs = false;
boolean mirrorXButtons = false;
boolean mirrorYButtons = false;

// END pin and PORT assignments

// ----------------------------

// Global variables 

byte byte0, byte1;                      // storage for incoming serial data

byte WaitingForAddress = 1;             // 1 when we expect the next serial byte to be an address value, 0 otherwise

byte address =  0x00;                   // garbage byte to hold address of function
byte state = 0x00;                      // garbage byte to hold state value
byte x = 0x00;                          // garbage byte to hold x position
byte y = 0x00;                          // garbage byte to hold y position
byte z = 0x00;                          // garbage byte to iterate over buttons

// The following variables are used to store flags that indicate whether we have received a given message,
// the value of the data in that message.  e.g. IntensityChange = 0 == no intensity change message received,
// IntensityChange = 1 == an intensity change message has been received, and it's value will be in IntensityVal
// The code that eventually acts upon the incoming message will reset the 'Change' variable to 0 once the 
// message has been handled.

byte IntensityChange = 0;               
byte IntensityVal = 0;                  

byte DisplayTestChange = 0;             
byte DisplayTestVal = 0;                

byte ShutdownModeChange = 0;            
byte ShutdownModeVal= 0;

// These variables are used to handle the ADC messages, and store which ports are currently enabled,
// and which are not.
byte ADCnum;
byte ADCstate;
byte ADCEnableState[4];

byte ledmem[8];                         // memory for LED states - 64 bits.

byte j = 0;                             // temporary variable for button looping
int i = 0;                              // temporary variable for looping etc.
int id = 0;                             // temporary storage for incoming message ID
byte firstRun = 1;                      // 1 when we have yet to receive an LED command, 0 after that.
                                        // used to ensure that our led state memory is properly initialized when we receive the first LED message

int kButtonUpDefaultDebounceCount   = 12;  // Used in button debouncing

int kButtonNewEvent   = 1;              // Used to store whether the state of a button has changed or not.

byte t = 0;                            // temporary variable used in button processing

/* BUTTON ARRAY VARIABLES 
 
 For 1/0 button states, use 8 bytes (64 bits)
 For button debounce counter, use 8x8 array
 
 */
byte button_current[8];
byte button_last[8];
byte button_state[8];
byte button_debounce_count[8][8];
byte button_event[8];
/* END OF BUTTON ARRAY VARIABLES */

/* MAX 7219 INSTRUCTION ADDRESSES */

byte max7219_reg_noop        = 0x00;    // define max7219 registers (read the tech doc for explaination)
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

/* END OF MAX 7219 INSTRUCTION ADDRESSES */

// putByte - helper function that sends a single byte to the MAX chip
void putByte(byte data) 
{
  byte i = 8;
  byte mask;

  while(i > 0)
  {
    mask = 0x01 << (i - 1);      // get bitmask


    if (data & mask)  // check and send value of this bit
    {            
      LED_DATA_PORT |= DataMaskHigh; 
    }
    else
    {                     
      LED_DATA_PORT &= DataMaskLow;  
    }

    // Pulse the MAX clock
    LED_CLOCK_PORT &= ClockMaskLow; //    digitalWrite( clock, LOW);   // "tick" prepeare for bit input
    LED_CLOCK_PORT |= ClockMaskHigh;//    digitalWrite(clock, HIGH);   // "tock" input bit

    --i;                         // move to lesser bit
  }
}


//maxSingle is the "easy"  function to use for a single max7219
//dig is the row call, and seg is the column call dig and seg refer to pin names from tech doc

void maxSingle( byte dig, byte seg) { 

  LED_LOAD_PORT &= LoadMaskLow;  //  digitalWrite(load, LOW);            // begin     

  putByte(dig);                       // specify register
  putByte(seg);                       //((data & 0x01) * 256) + data >> 1); // put data   

  LED_LOAD_PORT |= LoadMaskHigh; //  digitalWrite(load,HIGH); 

}


// buttonInit - helper function that zeros the button states
void buttonInit(void){
  byte i;
  for (i = 0; i < 8; i++) {
    button_current[i] = 0x00;
    button_last[i] = 0x00;
    button_state[i] = 0x00;
    button_event[i] = 0x00;
  }
}


// buttonCheck - checks the state of a given button.
void buttonCheck(byte row, byte index)
{
  if (((button_current[row] ^ button_last[row]) & (1 << index)) &&   // if the current physical button state is different from the
  ((button_current[row] ^ button_state[row]) & (1 << index))) {  // last physical button state AND the current debounced state

    if (button_current[row] & (1 << index)) {                      // if the current physical button state is depressed
      button_event[row] = kButtonNewEvent << index;              // queue up a new button event immediately
      button_state[row] |= (1 << index);                         // and set the debounced state to down.
    }
    else{
      button_debounce_count[row][index] = kButtonUpDefaultDebounceCount;
    }  // otherwise the button was previously depressed and now
    // has been released so we set our debounce counter.
  }
  else if (((button_current[row] ^ button_last[row]) & (1 << index)) == 0 &&  // if the current physical button state is the same as
  (button_current[row] ^ button_state[row]) & (1 << index)) {        // the last physical button state but the current physical
    // button state is different from the current debounce 
    // state...

    if (button_debounce_count[row][index] > 0 && --button_debounce_count[row][index] == 0) {  // if the the debounce counter has
      // been decremented to 0 (meaning the
      // the button has been up for 
      // kButtonUpDefaultDebounceCount 
      // iterations///

      button_event[row] = kButtonNewEvent << index;    // queue up a button state change event

      if (button_current[row] & (1 << index)){          // and toggle the buttons debounce state.
        button_state[row] |= (1 << index);
      }
      else{
        button_state[row] &= ~(1 << index);
      }
    }
  }
}


void buttonpress ()
{  
  for(i = 0; i < 8; i++){
    LATCH_PORT_595 &= latchPin595MaskLow;// set latch pin low so the outputs don't change while sending in bits
    for (j=0;j<8;j++){
      CLOCK_PORT_595 &= clockPin595MaskLow;//digitalWrite(clockPin,LOW);
      if (j==i){//if index equal current i value, set low
        DATA_PORT_595 &= dataPin595MaskLow;//digitalWrite(A4,LOW);
      }
      else{//set the rest of the pins high
        DATA_PORT_595 |= dataPin595MaskHigh;//digitalWrite(A4,HIGH);
      }
      CLOCK_PORT_595 |= clockPin595MaskHigh;//digitalWrite(clockPin,HIGH);
    }


    //set latch pin high- this sends data to outputs
    LATCH_PORT_595 |= latchPin595MaskHigh;//digitalWrite(latchPin, HIGH);

    // SlowDown is put in here to waste a little time while we wait for the state of the output
    // pins to settle.  Without this time wasting loop, a single button press would show up as
    // two presses (the button and its neighbour)
    volatile int SlowDown = 0; 

    while (SlowDown < 15) { 
      SlowDown++; 
    } 
    button_last [i] = button_current [i]; 

    for(id = 0; id < 8; id++) {
      switch (id){
        case 0:
        t = digitalRead(A0);
        break;
        case 1:
        t = digitalRead(A1);
        break;
        case 2:
        t = digitalRead(2);
        break;
        case 3:
        t = digitalRead(3);
        break;
        case 4:
        t = digitalRead(4);
        break;
        case 5:
        t = digitalRead(5);
        break;
        case 6:
        t = digitalRead(6);
        break;
        case 7:
        t = digitalRead(7);
        break;
      }
      t = (t == 0);//invert t
      if(t){
        button_current [i] |= (1 << id);
      }
      else{
          button_current [i] &= ~(1 << id);
      }
      buttonCheck(i, id);
      if (button_event[i] & (1 << id)) {
        button_event[i] &= ~(1 << id);//zero button event
        if(button_state[i] & (1 << id)){
          Serial.write(1);
        }
        else{
          Serial.write(byte(0));
        }
        
        if (mirrorXButtons){
          id=7-id;
        }
        if (mirrorYButtons){
          i=7-i;
        }
        Serial.write(((id) << 4) | (i));
      } 
    }
  } 
  
  //set all pins of 595 high
  LATCH_PORT_595 &= latchPin595MaskLow;// set latch pin low so the outputs don't change while sending in bits
    
    for (j=0;j<8;j++){
      CLOCK_PORT_595 &= clockPin595MaskLow;//digitalWrite(clockPin,LOW);
      DATA_PORT_595 |= dataPin595MaskHigh;//digitalWrite(A4,HIGH);
      CLOCK_PORT_595 |= clockPin595MaskHigh;//digitalWrite(clockPin,HIGH);
    }
    //set latch pin high- this sends data to outputs
    LATCH_PORT_595 |= latchPin595MaskHigh;//digitalWrite(latchPin, HIGH);

}

ISR(TIMER2_COMPA_vect) {

  do 
  {
    if (Serial.available())
    {
      if (WaitingForAddress == 1)
      {
        byte0 = Serial.read();

        address = byte0 >> 4;
        WaitingForAddress = 0;
      } // end if (WaitingForAddress == 1);

      if (Serial.available())
      {
        WaitingForAddress = 1;
        byte1 = Serial.read();

        switch(address)
        {
        case 2:
          state = byte0 & 15;
          x = byte1 >> 4;
          y = byte1 & 15;

          if (state == 0){
            ledmem[7-y] &= ~( 1 << x); 
          }
          else {
            ledmem[7-y] |=  ( 1 << x);
          }
          break;
        case 3:
          IntensityChange = 1;
          IntensityVal = byte1 & 15;          
          break;
        case 4:
          DisplayTestChange = 1;
          DisplayTestVal = byte1 & 15;
          break;
        case 5:
          state = byte1 & 0x0F;
          ADCEnableState[(byte1 >> 4)&0x03] = state;
          break;
        case 6:
          ShutdownModeChange = 1;
          ShutdownModeVal= byte1 & 15;
          break;
        case 7:
          if (firstRun == 1) {
            for (x = 0; x < 8; x++) {
              ledmem[x] = 0;
            }

            firstRun = 0;
          }

          x = ((byte0 & 15) & 0x7); // mask this value so we don't write to an invalid address.
          y = byte1;
          
          if (mirrorYLEDs){
            y=7-y;
          }
          if (mirrorXLEDs){
            x=flipByte(x);
          }

          ledmem[x] = y;
          break;
        case 8:
          if (firstRun == 1)
          {
            for (x = 0; x < 8; x++)
            {
              ledmem[x] = 0;
            }

            firstRun = 0;
          }

          x = ((byte0 & 15) & 0x7);
          y = byte1;

          if (mirrorYLEDs){
            x=7-x;
          }
          if (mirrorXLEDs){
            y=flipByte(y);
          }
          for (z = 0; z < 8; z++)
          {
            if (y & (1 << z))
            {
              ledmem[z] |= 1 << x;
            }
            else
            {
              ledmem[z] &= ~(1 << x);
            }
          }
          break;
        } // end switch(address)
      } // end if (Serial.available()
    } // end if (Serial.available();
  } // end do
  while (Serial.available() > 16);
}

void whoosh(void)
{
  // reactivate overflow interrupt for
  // timer 1 - it's needed by delay(...)
  TIMSK0 |= (1 << TOIE0); 

  for (int j = 0; j < 9; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      maxSingle(i+1,1<<j);
    }
    delay(125);
  }
  // and switch the interrupt off.
  TIMSK0 &= ~(1 << TOIE0);
}

void setup () {

  DDRD = PORTD_Data_Direction;
  DDRB = PORTB_Data_Direction;
  DDRC = PORTC_Data_Direction;

  Serial.begin(57600);

  buttonInit();  

  //initiation of the max 7219
  maxSingle(max7219_reg_scanLimit, 0x07);      
  maxSingle(max7219_reg_intensity,0x0F);
  maxSingle(max7219_reg_shutdown, 0x01);           // not in shutdown mode
  maxSingle(max7219_reg_displayTest, 0x00);        // empty registers, turn all LEDs off h

  for (i=1; i<=8; i++){
    maxSingle(i,0);
    ledmem[i-1]=0;
  }
  
  cli();//stop interrupts

  //set timer2 interrupt every 128us
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 7.8khz increments
  OCR2A = 255;// = (16*10^6) / (7812.5*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS11 bit for 8 prescaler
  TCCR2B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  sei();//allow interrupts

//  // Set up 8-bit counter 2, output compare switched off,
//  // normal waveform generation (whatever that might mean)
//  TCCR2A = 0;
//  // set counter to be clocked at 16Mhz/8 = 2Mhz
//  TCCR2B = 1<<CS21;
//
//  // set the interrupt mask so that we get an interrupt
//  // on timer 2 overflow, i.e. after 256 clock cycles.
//  // The timer 2 interrupt routine will execute every
//  // 128 uS.
//  TIMSK2 = 1<<TOIE2;
//
//  // NOTE: In my efforts to try to get this
//  // code to work reliably at 115200 baud
//  // I went about disabling unused timers that
//  // are set up by the Arduino framework.
//  // The framework sets up both timer 2 and 
//  // timer 1.  We use timer 2 to drive the
//  // serial reading interrupt, so we can only
//  // disable timer1 and its interrupt.
//
//  // REALLY IMPORTANT NOTE - IF YOU WANT TO USE
//  // ANALOGWRITE
//
//  // Disabling timer 1 will switch off the timer
//  // used for PWM, which underlies analogWrite.
//  // If you want to use analogWrite, remove
//  // the lines below.
//
//  // DISABLE PWM COUNTER
//  TIMSK0 &= ~(1 << TOIE0);
//
//  TCCR1B &= ~(1 << CS12);
//  TCCR1B &= ~(1 << CS11);
//  TCCR1B &= ~(1 << CS10);  
//  // END DISABLE PWM COUNTER
//
//  // Also, disable the interrupts on timer 0
//  // REALLY IMPORTANT NOTE IF YOU WANT TO USE
//  // DELAY
//  // remove this line, and also look at
//  // 'whoosh', which enables and then disables
//  // the intterupt on timer 0.  You'll want
//  // to get rid of those lines too.
//  TIMSK0 &= ~(1 << TOIE0);

  // pretty pattern to assure me that the firmware's
  // uploaded properly.
  whoosh();

  // make sure to turn off the lights.
  for (int i = 0; i < 8; i++)
  {
    maxSingle(i+1,0);
  }
}  

//void sendADC(int port, int value) {
//  Serial.write((1 << 4) | ((port << 2) & 0x0C) | ((value >> 8) & 0x03));
//  Serial.write(value & 0xFF);
//}
//
//int current[4]; 
//int previous[4]; 
//int tolerance = 7;

//void checkADCs() {
//
//  for (int adcCounter = 0; adcCounter < 4; adcCounter++)
//  {
//
//    if (ADCEnableState[adcCounter] != 0)
//    {
//      current[adcCounter] = analogRead(adcCounter);
//
//      if (abs(previous[adcCounter]-current[adcCounter]) > tolerance)
//      {
//        previous[adcCounter] = current[adcCounter];
//        sendADC(adcCounter,current[adcCounter]);
//      }
//
//    }
//
//  }
//}

byte flipByte(byte numToFlip){
  byte mirror = 0;
  for (int j=0;j<8;j++){
    byte copy = numToFlip;
    mirror |= (copy>>j)&1;
    if (j<7){
      mirror = mirror << 1;
    }
  }
  return mirror;
}

void loop () {

  // send the LED states to the LED matrix.
  for (int i = 0; i < 8; i++)
  {
    byte ledmemMirror = 0;
    
    if (mirrorXLEDs){
      ledmemMirror=flipByte(ledmem[i]);
    } else {
      ledmemMirror = ledmem[i];
    }
    int y;
    if (mirrorYLEDs){
      y =(7-i)+1;
    } else {
      y = i+1;
    }
    maxSingle(y,ledmemMirror);    
  }

  if (IntensityChange == 1)
  {
    IntensityChange = 0;
    maxSingle(max7219_reg_intensity, IntensityVal & 15);
  }

  if (DisplayTestChange == 1)
  {
    DisplayTestChange = 0;
    maxSingle(max7219_reg_displayTest, DisplayTestVal & 15);
  }

  if (ShutdownModeChange == 1)
  {
    ShutdownModeChange = 0;
    maxSingle(max7219_reg_shutdown, ShutdownModeVal & 15); 
  }

  // check for button presses
  buttonpress();
  
//  // check the state of the ADCs
//  checkADCs();  
}
