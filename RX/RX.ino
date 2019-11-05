#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>

RF24 radio(9,10); 
Servo servo;

byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  
byte gotPack[2], DirX, DirY, Forward, Backward; 

void setup()
{
  servo.attach(8);
  radio.begin();  
  radio.setAutoAck(0);         
  radio.setRetries(0,15);     
  radio.enableAckPayload();    
  radio.setPayloadSize(2);     
  radio.openReadingPipe(1,address[0]);      
  radio.setChannel(0x66);  
  radio.setPALevel (RF24_PA_MAX);
  radio.setDataRate (RF24_250KBPS);
  radio.powerUp(); 
  radio.startListening(); 
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT); 
}

void loop() 
{
    byte pipeNo;                         
    while( radio.available(&pipeNo))
      radio.read(&gotPack, sizeof(gotPack));
    DirX = gotPack[0];
    DirY = gotPack[1];
    if (DirX < 132)
      Backward = map(DirX, 0, 131, 255, 0);
    else
      Forward = map(DirX, 132, 255, 0, 255);
    if (Forward > 0)
      Backward = 0;
    analogWrite(7, Forward);
    analogWrite(4, Backward);
    Serial.print(Forward);
    Serial.print("  "); 
    Serial.print(Backward);
    Serial.print("  ");
    Serial.println(DirY);
    servo.write(DirY);     
}
