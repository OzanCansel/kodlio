
/* Kodlio 
*  01-08-2017 13:18 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int pot = 0;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(9, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(A0, INPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	pot = analogRead(A0);
	while(pot <= 300)
	{
		digitalWrite(9, HIGH);
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		break;	
}

	while(pot > 300 && pot <= 600)
	{
		digitalWrite(9, LOW);
		digitalWrite(10, HIGH);
		digitalWrite(11, LOW);
		break;	
}

	while(pot > 600)
	{
		digitalWrite(9, LOW);
		digitalWrite(10, LOW);
		digitalWrite(11, HIGH);
		break;
	}




}
