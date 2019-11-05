#include <SPI.h>          
#include "nRF24L01.h"     
#include "RF24.h"       

RF24 radio(9, 10); 

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб
byte Pack[2];

void setup() 
{
  radio.begin(); 
  radio.setAutoAck(0);        
  radio.setRetries(0, 15);    
  radio.enableAckPayload();   
  radio.setPayloadSize(2);  
  radio.openWritingPipe(address[0]); 
  radio.setChannel(0x66); 
  radio.setPALevel (RF24_PA_MAX); 
  radio.setDataRate (RF24_250KBPS); 
  radio.powerUp();
  radio.stopListening(); 
}

void loop() 
{
  Pack[0] = map(analogRead(0), 0, 1023, 0, 255);
  Pack[1] = map(analogRead(1), 0, 1023, 90-45, 90+45);
  radio.write(&Pack, sizeof(Pack));
  Serial.print(Pack[0]);
  Serial.print("  ");
  Serial.println(Pack[1]); 
}
