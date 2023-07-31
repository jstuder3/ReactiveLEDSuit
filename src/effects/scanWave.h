#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class ScanWave : Effect {

	public:
		const float speed = 20;
		const Color color{255, 255, 255};

	public:
		ScanWave() : Effect() {};
		ScanWave(MixingMode mixingMode) : Effect("ScanWave", mixingMode){}

		void update() {
				int position = int(floor(millis()-startTime * speed)) % Devices::getInstance().stripLEDs;
				for(auto strip : Devices::getInstance().strips){
					strip.setPixelColor(position, color.r, color.g, color.b);
				}
		}

};
