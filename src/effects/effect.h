#include "other/utils.h"
#include "devices.h"

#pragma once

class Effect{

	public:
		//Device device;
		String name = "BasicEffect";
		MixingMode mixingMode = MixingMode::Additive;
		unsigned long startTime = 0;
		unsigned long endTime = 0;
		bool infiniteDuration = false;

	public:
		Effect(){} // : startTime(millis()), endTime((unsigned long)-1) {} //set endTime to maxvalue of unsigned long
		Effect(String name) : name(name) {}

		virtual void update() {
			Serial.println("Updating in Effect.h. This should not happen. Make sure to add 'override' to the update function of your effect!");
		};

		bool isActive(){
			return infiniteDuration || millis() <= endTime;
		}

		/*void stopEffect(){
			endTime = millis();
		}*/

};
