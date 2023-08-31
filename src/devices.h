#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <MPUCustom.h>
#include <Wire.h>

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

#ifdef ESP_32
	#define STRIP_PIN_0 GPIO_NUM_32
	#define STRIP_PIN_1 GPIO_NUM_33
	#define STRIP_PIN_2 GPIO_NUM_25
	#define STRIP_PIN_3 GPIO_NUM_26
	#define MATRIX_PIN_0 GPIO_NUM_27
#endif

#define NUM_LED_STRIPS 4
#define NUM_LEDS_PER_STRIP 60
#define NUM_MPUS 1

class Devices {
		public:
			Adafruit_NeoPixel* strips[NUM_LED_STRIPS];
			uint8_t leftStrips[NUM_LED_STRIPS / 2] = {0, 1};
			uint8_t rightStrips[NUM_LED_STRIPS / 2] = {2, 3};

			Adafruit_NeoMatrix* matrix;

			//MPU* mpus[NUM_MPUS];

			MPUCustom* mpus[NUM_MPUS];
			int mpu_addresses[2] = {0x68, 0x69};

		public:

			static Devices& getInstance() {
				static Devices instance; // Guaranteed to be destroyed and instantiated on first use.
				return instance;
    	}

			void initAll(){

				// LED STUFF

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

				// SENSOR STUFF
				
				for(int i = 0; i < NUM_MPUS; i++){
					mpus[i]= new MPUCustom(Wire, mpu_addresses[i]);
					mpus[i]->begin(2); // set value range to +/- [2, 4, 8, 16] g
				}
				
			}

	void updateSensors(){

		for(MPUCustom* mpu : mpus){
			mpu->update();

			/*
			float ax = mpu->getAccX();
			float ay = mpu->getAccY();
			float az = mpu->getAccZ();
			float tot = mpu->getTotalAcc();
			float ws_tot = mpu->getWeaklySmoothedTotalAcc();
			float ss_tot = mpu->getStronglySmoothedTotalAcc();
			String printval = "ax:" + String(ax) + ",ay:" + String(ay) + ",az:" + String(az) + ",tot:" + String(tot) + ",ws_tot:" + String(ws_tot) + ",ss_tot:" + String(ss_tot);
			Serial.println(printval);*/
		}

	}

};
