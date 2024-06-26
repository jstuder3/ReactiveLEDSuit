#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class Blinking : public Effect {

	public:

		unsigned long onDuration = 1000;
		unsigned long offDuration = 1000;
		unsigned long totalDuration = onDuration + offDuration;
		Color color{100, 100, 100};

	public:
		Blinking(Adafruit_NeoPixel* strip) : Effect("Blinking", strip) {
			infiniteDuration = true;
		}

		void update() override {
			//Serial.println(millis() % totalDuration < onDuration);
			if((millis()-startTime) % totalDuration < onDuration){
				for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
					strip->setPixelColor(i, color.r, color.g, color.b);
				}
			}
			else{
				//do nothing
			}

			}

};
