#include "output/strips.h"
#include "other/utils.h"

int colors[NUM_LEDS];

Strips::Strips(){
			strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

			strip.begin();
			strip.show(); // Initialize all pixels to 'off'
		}

void Strips::update(){
	advanceOneStep();
	colors[0] = uint8_t(255 * 0.5);
	setColors();
}

void Strips::advanceOneStep()
{
	for (int i = strip.numPixels(); i >= 1; i--)
	{
		colors[i] = colors[i - 1];
	}
	colors[0] = 0;
}

void Strips::setColors()
{
	for (int i = 0; i < strip.numPixels(); i++)
	{
		Color col = Utils::intToColor(colors[i]);
		// strip.setPixelColor(i, col.r, col.g, col.b);
		// strip.setPixelColor(i, col.b, col.b, col.b);
		const int val = colors[i] > 200 ? 255 : 0;
		strip.setPixelColor(i, val, val, val);
	}
	strip.show();
}
