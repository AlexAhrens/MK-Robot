#include <SPI.h>
#include "RF24.h"

RF24 myRadio (A0, A1);
byte addresses[][6] = {"0"};

struct package
{
  int X = 0;
  int Y = 0;
  bool Button0;
  int V_X = 0;
  int V_Y = 0;
};

typedef struct package Package;
Package data;

int Speed = 100;
int Mitte_X = 502;
int Mitte_Y = 508;

void setup()
{ 
  myRadio.begin();
  myRadio.setChannel(135);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
  delay(250);
  pinMode(9,OUTPUT);
  
  pinMode(A2,OUTPUT); //Hinten rechts
  pinMode(A3,OUTPUT);

  pinMode(3,OUTPUT);  //Vorne links
  pinMode(4,OUTPUT);
  
  pinMode(A4,OUTPUT); //Hinten rechts
  pinMode(A5,OUTPUT);
  
  pinMode(8,OUTPUT);  //Vorne rechts
  pinMode(2,OUTPUT);
}

void loop()
{
  Empfangen();
  Fahren();
}

void Empfangen()
{
  if ( myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
      delay(20);
    }
  }
}

void Fahren()
{
if (data.X > (Mitte_X + 10))
  {
    moveForward();
    delay(10);
  }
else if (data.X < (Mitte_X - 10))
  {
    moveBackward();
    delay(10);
  }
else if (data.Y > (Mitte_Y + 10))
  {
    moveRight();
    delay(10);
  }
else if (data.Y < (Mitte_Y - 10))
  {
    moveLeft();
    delay(10);
  }
else if(data.Button0==0)
  {
    turn();
    delay(10);
  }
else
  {
    Stop();
    delay(10);  
  }
}

void Stop()
{
 analogWrite(9,0);
  digitalWrite(A2,LOW);   //HR
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);  //HL
  digitalWrite(A5,LOW);
  digitalWrite(8,LOW);  //VR
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);    //VL
  digitalWrite(4,LOW);
}
void moveForward()
{
 analogWrite(9,Speed);
  digitalWrite(A2,LOW);   //HR
  digitalWrite(A3,HIGH);
  digitalWrite(A4,HIGH);  //HL
  digitalWrite(A5,LOW);
  digitalWrite(8,HIGH);  //VR
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);    //VL
  digitalWrite(4,HIGH);
}
void moveBackward()
{
 analogWrite(9,Speed);
  digitalWrite(A2,HIGH);   //HR
  digitalWrite(A3,LOW);
  digitalWrite(A4,LOW);  //HL
  digitalWrite(A5,HIGH);
  digitalWrite(8,LOW);  //VR
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);    //VL
  digitalWrite(4,LOW);
}

void moveLeft() 
{
 analogWrite(9,Speed);
  digitalWrite(A2,LOW);   //HR
  digitalWrite(A3,HIGH);
  digitalWrite(A4,LOW);  //HL
  digitalWrite(A5,HIGH);
  digitalWrite(8,HIGH);  //VR
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);    //VL
  digitalWrite(4,LOW);
}

void moveRight() 
{  
  analogWrite(9,Speed);
  digitalWrite(A2,HIGH);   //HR
  digitalWrite(A3,LOW);
  digitalWrite(A4,HIGH);  //HL
  digitalWrite(A5,LOW);
  digitalWrite(8,LOW);  //VR
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);    //VL
  digitalWrite(4,HIGH);
}

void turn()
{
 analogWrite(9,Speed);
 digitalWrite(A2,LOW);   //HR
 digitalWrite(A3,HIGH);
 digitalWrite(A4,LOW);  //HL
 digitalWrite(A5,HIGH);
 digitalWrite(8,LOW);  //VR
 digitalWrite(2,HIGH);
 digitalWrite(3,LOW);    //VL
 digitalWrite(4,HIGH); 
}
