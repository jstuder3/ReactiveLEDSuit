#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#pragma once

class Devices {
		public:
			Adafruit_NeoPixel strips[4];
			const int stripLEDs = 150;

			//NeoMatrix doesn't provide a default constructor, so we make this as a pointer
			Adafruit_NeoMatrix* matrix;

		public:

			static Devices& getInstance() {
        static Devices instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

			void initAll(){
				strips[0] = Adafruit_NeoPixel(stripLEDs, D8, NEO_GRB + NEO_KHZ800);
				strips[1] = Adafruit_NeoPixel(stripLEDs, D7, NEO_GRB + NEO_KHZ800);
				strips[2] = Adafruit_NeoPixel(stripLEDs, D6, NEO_GRB + NEO_KHZ800);
				strips[3] = Adafruit_NeoPixel(stripLEDs, D5, NEO_GRB + NEO_KHZ800);

				matrix = new Adafruit_NeoMatrix(32, 8, D0,
											NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
											NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
											NEO_GRB            + NEO_KHZ800);

				for(auto strip : strips){
					strip.begin();
				}
				matrix->begin();

				matrix->setTextWrap(false);
				matrix->setBrightness(255); // Adjust brightness as necessary

				strips[0].setPixelColor(10, 255, 255, 255);
			}

	private:
		// Private Constructor
    Devices() {};

		// Prevent copy constructor and assignment operator
		Devices(const Devices&) = delete;  // No copy constructor
    Devices& operator=(const Devices&) = delete;  // No assignment operator

};
