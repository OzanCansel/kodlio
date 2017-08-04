
/* Kodlio 
*  03-08-2017 15:32 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();

void ledyakma()
{
	digitalWrite(9, HIGH);
	delay(500);
	digitalWrite(9, LOW);
	delay(500);
}

void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(9, OUTPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	ledyakma();
}
