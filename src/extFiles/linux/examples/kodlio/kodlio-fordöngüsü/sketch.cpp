
/* Kodlio 
*  28-07-2017 14:45 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int i = 0;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
pinMode(10, OUTPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
for(i = 0; i<=255; i++)
{
analogWrite(10, i);
delay(5);
}
for(i = 255; i>=0; i--)
{
analogWrite(10, i);
delay(5);
}

}
