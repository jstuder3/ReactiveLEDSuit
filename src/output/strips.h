#include <Adafruit_NeoPixel.h>
#include "other/utils.h"

#define LED_PIN    6  // Set to the pin where your strip is connected
#define NUM_LEDS   150 // Set to the number of LEDs on your strip

class Strips{

	private:
		Adafruit_NeoPixel strip;

	public:
		Strips();
		void update();

	private:
		void advanceOneStep();
		void setColors();

};
