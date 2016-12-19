
#include <SPI.h>
#include <MFRC522.h>
 
#define doorPin 8
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String cards[]={
                "36 59 CC 94",
                "36 59 CC 92",
                "36 59 CC 94",
                "7C 0D 95 A6",
                "36 59 CC 94",
                "36 59 CC 94",
                "36 59 CC 93",
                };
int cardCount =  7;          // How Many Cards
 
void setup() 
{
  pinMode(doorPin, OUTPUT);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.print("Cards in database ");
  Serial.println(cardCount);
  Serial.println();
}
void loop() 
{
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
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();

  for (byte j = 0; j < cardCount; j++) 
  {
  if (content.substring(1) == cards[j] )   
      {
        Serial.println();
        Serial.println("Authorized access");
        Serial.println();
        digitalWrite(doorPin,HIGH);  //Send trigger to OPEN DOOR STRIKE!!!
        delay(3000);
        digitalWrite(doorPin,LOW);   //Send trigger to CLOSE DOOR STRIKE!!!
        return;
      }
 
  } 
       
       Serial.println();
       Serial.println(" Access denied");
       Serial.println();
       delay(3000);
       
     
  
} 
