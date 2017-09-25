
/* Kodlio 
*  02-08-2017 15:32 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int led = 9;
char komut;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	Serial.begin(9600);
	pinMode(led, OUTPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	komut = Serial.read();

	switch (komut)
	{
		case 'a':
		digitalWrite(led, HIGH);
		break;

		case 'k':
		digitalWrite(led, LOW);
		break;
	}
}
