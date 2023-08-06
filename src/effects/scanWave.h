#include <math.h>
#include <Arduino.h>
#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class ScanWave : public Effect {

	public:
		const float speed = 30;
		const float tailLength = 15;
		const Color color{255, 255, 255};

	public:
		ScanWave(Adafruit_NeoPixel* strip) : Effect("ScanWave", strip) {
		}

		ScanWave(EffectConfiguration& config) : Effect(config) {
			infiniteDuration = true;
			name = "ScanWave";
		}

		void update() override {
				float floatPosition = fmod(((millis()-startTime) / 1000.f) * speed, (strip->numPixels()+tailLength));

				int head = min(ceil(floatPosition), (float)NUM_LEDS_PER_STRIP);
				int tail = max(floor(floatPosition-tailLength), 0.f);
				for(int i = head; i >= tail; i--){
					float distanceToActualPosition = abs((float)i - floatPosition);
					float multiplier;
					if(i == head){
						multiplier = pow(1.f - distanceToActualPosition, 2);
					}
					else{
						multiplier = pow(1.f - (distanceToActualPosition/tailLength), 2);
					}

					strip->setPixelColor(i, int(multiplier * color.r), int(multiplier*color.g), int(multiplier * color.b));


				}
		}
/*
		*/
};
