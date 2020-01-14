// RFID Reader -> Wire Slave Sender
// by Nevin Danielson

// Receive a request from a Master using the Wire library
// Check for the correct RFID UID
// Sends confirmation as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 22 August 2018

#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}

void loop() {
  delay(10000);
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
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  if (content.substring(1) == "BD 3C 2E 2C") //change here the UID of the card/cards that you want to give access
  {
    Wire.onRequest(requestEvent); // register event
    delay(3000);
 }
 
 else   {
      }
 
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("Y"); // respond with message of 6 bytes
  // as expected by master
}
