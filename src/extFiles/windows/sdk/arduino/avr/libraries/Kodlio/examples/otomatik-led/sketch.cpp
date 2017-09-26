
/* Kodlio 
*  31-07-2017 16:21 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int isikseviyesi = 0;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
pinMode(8, OUTPUT);
pinMode(A0, INPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	isikseviyesi = analogRead(A0);
	if(isikseviyesi <= 250)
	{
		digitalWrite(8, HIGH);
	}
	if(isikseviyesi > 250)
	{
		digitalWrite(8, LOW);
	}

}
