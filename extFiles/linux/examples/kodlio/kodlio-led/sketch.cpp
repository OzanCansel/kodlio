#include<Arduino.h>

void setup();
void loop();

void setup()
{
pinMode(8, OUTPUT);
}

void loop()
{
digitalWrite(8, HIGH);
}