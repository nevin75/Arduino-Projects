#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
const int buttonPin = 2;  // Set a button to any pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

#define SS_PIN 10
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup()
{
  pinMode(buttonPin, INPUT);  // Set the button as an input

  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();


  
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
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "BD 3C 2E 2C") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
  if (content.substring(1) == "BD 3C 2E 2C") //change here the UID of the card/cards that you want to give access
 {Keyboard.println("Wicket35");;
    delay(100);
    Keyboard.println("Wicket35");
    delay (1000);
    }
}
