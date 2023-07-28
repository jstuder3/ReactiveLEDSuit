#include "effectController.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

EffectController::EffectController() {
	strips[0] = Adafruit_NeoPixel(stripLength, D8, NEO_GRB + NEO_KHZ800);
	strips[1] = Adafruit_NeoPixel(stripLength, D7, NEO_GRB + NEO_KHZ800);
	strips[2] = Adafruit_NeoPixel(stripLength, D6, NEO_GRB + NEO_KHZ800);
	strips[3] = Adafruit_NeoPixel(stripLength, D5, NEO_GRB + NEO_KHZ800);

	initAll();

}

void EffectController::update(){
	Serial.println("Updated EffectController");

	//do something with the LEDs here

		/*mat.fillScreen(65535);
	mat.show();
	//strip1.setPixelColor(0, strip1.Color(255, 255, 255));
	//strip1.show();
	delay(1);

	mat.fillScreen(0);
	mat.show();
	//strip1.setPixelColor(0, strip1.Color(0, 0, 0));
	//strip1.show();
	delay(200);*/


/*
		unsigned long startTime = millis();

		int color = 10;
		for(int i = 0; i < strip1.numPixels(); i++){
			strip1.setPixelColor(i, millis() % 255, millis() % 254, millis() % 253);
			strip2.setPixelColor(i, millis() % 252, millis() % 251, millis() % 250);
			strip3.setPixelColor(i, millis() % 249, millis() % 248, millis() % 247);
			strip4.setPixelColor(i, millis() % 246, millis() % 245, millis() % 244);
		}

		showAll();
		//delay(50);

		int timeTaken = int(millis()-startTime);
		averageTime = averageTime * alpha + (1-alpha) * timeTaken;

		if(millis() % 10 == 0){
			Serial.println(averageTime);
		}

		clearAll();
		showAll();
		//delay(50);
*/



	/*Serial.println("Showing strip 1");
	setActiveAndDelay(&strip1, 255, 2000);
	Serial.println("Showing strip 2");
	setActiveAndDelay(&strip2, 255, 2000);
	Serial.println("Showing strip 3");
	setActiveAndDelay(&strip3, 255, 2000);
	Serial.println("Showing strip 4");
	setActiveAndDelay(&strip4, 255, 2000);
	Serial.println("Showing matrix");
	setActiveAndDelay(&mat, 255, 2000);*/

	/*for(int i = 0; i<150; i++){
		strip.setPixelColor(i, 255, 255, 255);
	}
	strip.show();
	//Serial.print("Set to WHITE\n");
	delay(500);
		for(int i = 0; i<150; i++){
		strip.setPixelColor(i, 0, 0, 0);
	}
	strip.show();
	//Serial.print("Set to BLACK\n");
	delay(500);*/
	//Serial.println("Nothing happening...");
	//delay(1000);
}

/*void setActiveAndDelay(Adafruit_NeoPixel* but, int color, int del){
	clearAll();
	for(int i = 0; i < but->numPixels(); i++){
		but->setPixelColor(i, color, color, color);
	}
	showAll();
	delay(del);
}*/

void EffectController::removeExpired(){

}

void EffectController::initAll(){
	for(auto strip : strips){
		strip.begin();
	}
	matrix.begin();

	matrix.setTextWrap(false);
  matrix.setBrightness(255); // Adjust brightness as necessary
}

void EffectController::clearAll(){
	for(auto strip : strips){
		strip.clear();
	}
	matrix.clear();
}

void EffectController::showAll(){
	for(auto strip : strips){
		strip.show();
	}
	matrix.show();
}
