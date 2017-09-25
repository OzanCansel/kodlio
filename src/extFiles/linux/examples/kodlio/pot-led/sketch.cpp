#include<Arduino.h>

void setup();
void loop();

void setup()
{
pinMode(A0, INPUT);
pinMode(9, OUTPUT);
}

void loop()
{
analogWrite(analogRead(A0) / 4);
}