#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class ScanWave : public Effect {

	public:
		const float speed = 30;
		const float tailLength = 15;
		const Color color{50, 0, 0};

	public:
		ScanWave(Adafruit_NeoPixel* strip) : Effect("ScanWave", strip) {
			infiniteDuration = true;
		}

		void update() override {
				float floatPosition = fmod(((millis()-startTime) / 1000.f) * speed, (strip->numPixels()+tailLength));

				int head = min(ceil(floatPosition), Devices::getInstance().numStripLEDs);
				int tail = max(floor(floatPosition-tailLength), 0);
				for(int i = head; i >= tail; i--){
					float distanceToActualPosition = abs((float)i - floatPosition);
					float multiplier;
					if(i == head){
						multiplier = square(1.f - distanceToActualPosition);
					}
					else{
						multiplier = square(1.f - (distanceToActualPosition/tailLength));
					}

					strip->setPixelColor(i, int(multiplier * color.r), int(multiplier*color.g), int(multiplier * color.b));


				}
		}
/*
		*/
};
