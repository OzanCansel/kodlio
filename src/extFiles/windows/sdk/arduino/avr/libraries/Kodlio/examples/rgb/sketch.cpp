#include<Arduino.h>

void setup();
void loop();

void setup()
{
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
}

void loop()
{
	analogWrite(9, 155);
	analogWrite(10, 155);
	analogWrite(11, 155);
}