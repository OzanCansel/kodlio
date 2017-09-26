
/* Kodlio 
*  27-07-2017 16:22 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();

int isikseviyesi = 0;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(A0, INPUT);
	pinMode(9, OUTPUT);

}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	isikseviyesi = analogRead(A0);
	isikseviyesi = isikseviyesi / 4;
	isikseviyesi = 255 - isikseviyesi;
	analogWrite(9, isikseviyesi);
}
