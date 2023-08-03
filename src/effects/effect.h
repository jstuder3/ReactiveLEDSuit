#include "other/utils.h"
#include "devices.h"

#pragma once

class Effect{

	public:
		//Device device;
		String name = "BasicEffect";
		unsigned long startTime = 0;
		unsigned long endTime = 0;
		bool infiniteDuration = false;
		Adafruit_NeoPixel* strip;
		Adafruit_NeoMatrix* matrix;

	public:
		Effect(){} // : startTime(millis()), endTime((unsigned long)-1) {} //set endTime to maxvalue of unsigned long
		Effect(String name) : name(name), startTime(millis()) {}
		Effect(String name, Adafruit_NeoPixel* strip) : name(name), strip(strip), startTime(millis()) {}
		Effect(String name, Adafruit_NeoMatrix* matrix) : name(name), matrix(matrix), startTime(millis()) {}

		virtual void update() {
			Serial.println("Updating in Effect.h. This should not happen. Make sure to add 'override' to the update function of your effect!");
		};

		bool isActive(){
			return infiniteDuration || millis() <= endTime;
		}

		//write the provided value to the assigned device
		/*void setPixel(int pixel, int red, int green, int blue){
			if(strip){
				strip->setPixelColor(pixel, red, green, blue);
			}
			if(matrix){
				matrix->setPixelColor(pixel, red, green, blue);
			}
		}*/

		/*void stopEffect(){
			endTime = millis();
		}*/

};
