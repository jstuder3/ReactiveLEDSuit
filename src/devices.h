#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#pragma once

//pins for Arduino Uno (note that this requires the -D ARDUINO_UNO build flag to work)
#ifdef ARDUINO_UNO
	#define STRIP_PIN_0 13
	#define STRIP_PIN_1 12
	#define STRIP_PIN_2 11
	#define STRIP_PIN_3 10
	#define MATRIX_PIN_0 9
#endif

// pins for D1 Mini (note that this requires the -D D1_MINI build flag to work)
#ifdef D1_MINI
	#define STRIP_PIN_0 D8
	#define STRIP_PIN_1 D7
	#define STRIP_PIN_2 D6
	#define STRIP_PIN_3 D5
	#define MATRIX_PIN_0 D0
#endif

#define NUM_LED_STRIPS 4
#define NUM_LEDS_PER_STRIP 60

class Devices {
		public:
			Adafruit_NeoPixel* strips[NUM_LED_STRIPS];
			uint8_t leftStrips[NUM_LED_STRIPS / 2] = {0, 1};
			uint8_t rightStrips[NUM_LED_STRIPS / 2] = {2, 3};

			Adafruit_NeoMatrix* matrix;

		public:

			static Devices& getInstance() {
				static Devices instance; // Guaranteed to be destroyed and instantiated on first use.
				return instance;
    	}

			void initAll(){
				strips[0] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_0, NEO_GRB + NEO_KHZ800);
				strips[1] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_1, NEO_GRB + NEO_KHZ800);
				strips[2] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_2, NEO_GRB + NEO_KHZ800);
				strips[3] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_3, NEO_GRB + NEO_KHZ800);

				matrix = new Adafruit_NeoMatrix(32, 8, MATRIX_PIN_0,
											NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
											NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
											NEO_GRB            + NEO_KHZ800);

				for(auto& strip : strips){
					strip->begin();
					strip->setBrightness(255);
					strip->clear();
					strip->show();
				}
				matrix->begin();

				matrix->setTextWrap(true);
				matrix->setBrightness(255); // Adjust brightness as necessary

			}

	private:
		// Private Constructor
    /*Devices() {};

		// Prevent copy constructor and assignment operator
		Devices(const Devices&) = delete;  // No copy constructor
    Devices& operator=(const Devices&) = delete;  // No assignment operator
		*/

};
