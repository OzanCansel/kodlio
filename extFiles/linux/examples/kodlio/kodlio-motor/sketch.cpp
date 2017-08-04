
/* Kodlio 
*  03-08-2017 15:32 tarihinde oluşturuldu.
*  Dosya:	sketch.cpp
*/

#include <Arduino.h>

void setup();
void loop();
int hiz = 9;
int uyku = 10;
int motor1 = 4;
int motor2 = 5;
void setup(){
	//Arduino ilk açıldığında çalıştırılcak komutlar buraya
	pinMode(hiz, OUTPUT);
	pinMode(uyku, OUTPUT);
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
}

void loop(){
	//Arduino sonsuz döngü için komutlar buraya
	digitalWrite(uyku, HIGH);
	digitalWrite(motor1, HIGH);
	digitalWrite(motor2, LOW);
	analogWrite(hiz, 155);
}
