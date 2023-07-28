#include <Arduino.h>
#include "effects/effect.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

class EffectController{

	public:
		Adafruit_NeoPixel strips[4];

		//NeoMatrix doesn't provide a default constructor, so this has to go here
		Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, D0,
  							NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  							NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  							NEO_GRB            + NEO_KHZ800);

		const int stripLength = 150;

	public:
		EffectController();

		void update();

		void removeExpired();
		void initAll();
		void clearAll();
		void showAll();

};
