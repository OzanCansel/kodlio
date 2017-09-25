
/* Kodlio 
*  02-08-2017 13:50 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>
int led = 9;
int ses = A0;
int sesseviyesi = 0;
int durum = 0;
void setup();
void loop();

void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(led, OUTPUT);
	pinMode(ses, INPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	sesseviyesi = analogRead(ses);
	if(sesseviyesi > 550)
	{
		durum = durum + 1;
		delay(300);
	}

	if(durum == 1)
	{
		digitalWrite(led, HIGH);
	}	

	if(durum == 2)
	{
		digitalWrite(led, LOW);
		durum = 0;
	}



}
