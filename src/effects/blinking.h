#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class Blinking : public Effect {

	public:

		unsigned long onDuration = 150;
		unsigned long offDuration = 900;
		unsigned long totalDuration = onDuration + offDuration;
		Color color{100, 100, 100};

	public:
		Blinking() : Effect("Blinking") {
			infiniteDuration = true;
		}

		void update() override {
			//Serial.println(millis() % totalDuration < onDuration);
			if(millis() % totalDuration < onDuration){
				for(int i = 0; i < 10; i++){
					Devices::getInstance().strips[0]->setPixelColor(i, color.r, color.g, color.b);
				}
			}
			else{
				//do nothing
			}

			}

};
