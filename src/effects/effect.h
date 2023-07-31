#include "other/utils.h"
#include "devices.h"

class Effect{

	public:
		//Device device;
		String name;
		MixingMode mixingMode;
		unsigned long startTime;
		unsigned long endTime;
		bool shouldLoop;

	public:
		Effect() : startTime(millis()), endTime((unsigned long)-1) {} //set endTime to maxvalue of unsigned long
		Effect(String name, MixingMode mixingMode) : name(name), mixingMode(mixingMode) {}

		void update() {};

		bool isActive(){
			return millis() <= endTime;
		}

		void stopEffect(){
			endTime = millis();
		}

};
