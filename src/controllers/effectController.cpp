#include "effectController.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include "devices.h"

void EffectController::update(){
	Serial.println("Updated EffectController");

	//do something with the LEDs here

	for(auto effect : effects){
		if(effect.isActive()){
			effect.update();
		}
	}

	for(int i = 0; i < Devices::getInstance().stripLEDs; i++){
		Devices::getInstance().strips[0].setPixelColor(i, 255, 255, 255);
	}

	delay(500);

	for(int i = 0; i < Devices::getInstance().stripLEDs; i++){
		Devices::getInstance().strips[0].setPixelColor(i, 0, 0, 0);
	}
}

bool EffectController::registerEffect(Effect &effect){
	for(uint8_t i = 0; i < sizeof(effects)/sizeof(Effect); i++){
		if(!effects[i].isActive()){
			effects[i] = effect;
			return true;
		}
	}
	//Serial.println("Couldn't register effect: No more space left")
	return false;
}

void EffectController::clearAll(){
	for(auto strip : Devices::getInstance().strips){
		strip.clear();
	}
	Devices::getInstance().matrix->clear();
}

void EffectController::showAll(){

	for(auto strip : Devices::getInstance().strips){
		strip.show();
	}
	Devices::getInstance().matrix->show();
}
