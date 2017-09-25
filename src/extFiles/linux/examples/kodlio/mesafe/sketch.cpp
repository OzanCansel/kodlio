
/* Kodlio 
*  28-07-2017 10:21 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();

void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
pinMode(8, OUTPUT);
pinMode(9, INPUT);
Serial.begin(9600);


}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
digitalWrite(8, HIGH);
delay(10);
digitalWrite(8, LOW);
long zaman, mesafe;
zaman = pulseIn(9, HIGH);
mesafe = zaman / 59.2;
Serial.print(mesafe);
Serial.println(" cm");
delay(250);
}
