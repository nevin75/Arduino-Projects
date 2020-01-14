#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 5
#define KEY_RETURN 0xB0      
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

MFRC522 mfrc522 ( SS_PIN, RST_PIN ) ;
char Enter = KEY_RETURN;                //Return key is declared as Enter.
String readid;
String card1="BD 3C 2E 2C";                //Change this value to the UID of your card.

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input

  
  Serial.begin(9600);
 Keyboard.begin();
 SPI.begin();
 mfrc522.PCD_Init();


  
}

void temp(byte *buffer, byte bufferSize)//function to store card uid as a string datatype.
{
  readid="";
  for(byte i = 0;i<bufferSize; i++)
  {
    readid=readid+String(buffer[i], HEX);
  }
}

void loop()
{

   
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) 
  {
    Keyboard.press('z');
    Keyboard.press('x');
    delay(50);
    Keyboard.releaseAll();
    delay (1000);
  }
   else {
    }

    // Look for new cards
  if(!mfrc522.PICC_IsNewCardPresent())
 {
  return;
 }
 if(!mfrc522.PICC_ReadCardSerial()) 
 {
  return;
 }
 mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // Display card details in serial Monitor.
 temp(mfrc522.uid.uidByte, mfrc522.uid.size);
 if(readid==card1)
 { 
  Keyboard.println("Wicket35");;
    delay(100);
    Keyboard.println("Wicket35");
    delay (1000);
 }
 else
 {
  return;
 }

}
