
/* Kodlio 
*  01-08-2017 14:58 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int mesafe = 0;
int zaman = 0;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(8, OUTPUT);
	pinMode(9, INPUT);
	pinMode(10, OUTPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	digitalWrite(8, HIGH);
	delay(10);
	digitalWrite(8, LOW);
	zaman = pulseIn(9, HIGH);
	mesafe = zaman / 59.2;
	if(mesafe < 30 && mesafe >=20)
	{
		digitalWrite(10, HIGH);
		delay(500);
		digitalWrite(10, LOW);
		delay(500);
	}

	if(mesafe < 20 && mesafe > 10)
	{
		digitalWrite(10, HIGH);
		delay(250);
		digitalWrite(10, LOW);
		delay(250);
	}

	if(mesafe < 10 && mesafe >= 5)
	{
		digitalWrite(10, HIGH);
		delay(100);
		digitalWrite(10, LOW);
		delay(100);
	}
	
	if(mesafe < 5)
	{
		digitalWrite(10, HIGH);
	}









}
