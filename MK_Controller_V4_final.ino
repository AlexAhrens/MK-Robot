#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (A0,10);
byte addresses[][6] = {"0"};

struct package
{
  int X= 1;
  int Y = 1;
  bool Button0;
  bool Button1;
  bool Button2;
  int V_X;
  int V_Y;
};

typedef struct package Package;
Package data;

void setup()
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT_PULLUP); 
  pinMode(3, INPUT_PULLUP); 
  delay(100);
  myRadio.begin();  
  myRadio.setChannel(135); 
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.setDataRate( RF24_250KBPS ); 
  myRadio.openWritingPipe( addresses[0]);
  delay(100);
}

void loop()
{
 Auslesen();
 Senden();
 Debug();
}
void Auslesen()
{
  data.X = analogRead(A1);
  data.Y = analogRead(A2);
  data.Button0 = analogRead(A3);
  data.Button1 = digitalRead(2);
  data.Button2 = digitalRead(3);
}

void Senden()
{
  myRadio.write(&data, sizeof(data));
  delay(100);
}

void Debug()
{
  Serial.begin(9600);
  Serial.println("X:");
  Serial.println(data.X);
  Serial.println("Y: ");
  Serial.println(data.Y);
  Serial.println("V_X:");
  Serial.println(data.V_X);
  Serial.println("V_Y: ");
  Serial.println(data.V_Y);
  Serial.println("B0: ");
  Serial.println(data.Button0);
  Serial.println("B1: ");
  Serial.println(data.Button1);
  Serial.println("B2: ");
  Serial.println(data.Button2);
}

