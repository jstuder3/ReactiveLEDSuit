#include "effectController.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include "devices.h"

void EffectController::update(){
	//Serial.println("Updated EffectController");

	//do something with the LEDs here

	clearAll();

	for(int i = 0; i < MAX_EFFECTS; i++){
		if(effects[i] && effects[i]->isActive()){
			effects[i]->update();
			//Serial.println(effects[i]->name);
		}
	}
	//Serial.println("Updated all effects");
	showAll();

}

bool EffectController::registerEffect(Effect* effect){
	for(int i = 0; i < MAX_EFFECTS; i++){
		if(!effects[i]){
			effects[i] = effect;
			return true;
		}
		else if(!effects[i]->isActive()){
			delete effects[i];
			effects[i] = effect;
			return true;
		}
	}
	//Serial.println("Couldn't register effect: No more space left")
	return false;
}

void EffectController::killAllEffects(){
	for(int i = 0; i < MAX_EFFECTS; i++){
		if(effects[i]){
			delete effects[i];
			effects[i] = nullptr;
		}
	}
}

void EffectController::clearAll(){
	for(Adafruit_NeoPixel* strip : Devices::getInstance().strips){
		strip->clear();
	}
	//Devices::getInstance().matrix->clear();
}

void EffectController::showAll(){

	for(Adafruit_NeoPixel* strip : Devices::getInstance().strips){
		strip->show();
	}
	//Devices::getInstance().matrix->show();
}
