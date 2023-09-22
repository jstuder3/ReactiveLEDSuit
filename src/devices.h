#include <Arduino.h>

#include <NeoPixelBus.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <MPUCustom.h>
#include <Wire.h>
#include "other/utils.h"

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

	#define STRIP_PIN_L_0 GPIO_NUM_32
	#define STRIP_PIN_L_1 GPIO_NUM_33
	#define STRIP_PIN_L_2 GPIO_NUM_25
	#define STRIP_PIN_L_3 GPIO_NUM_26
	#define STRIP_PIN_L_4 GPIO_NUM_27

	#define STRIP_PIN_R_0 GPIO_NUM_19
	#define STRIP_PIN_R_1 GPIO_NUM_18
	#define STRIP_PIN_R_2 GPIO_NUM_5
	#define STRIP_PIN_R_3 GPIO_NUM_17
	#define STRIP_PIN_R_4 GPIO_NUM_16

#endif

#define NUM_LED_STRIPS 10
#define NUM_LEDS_PER_STRIP 60
#define NUM_MPUS 0

class Devices {
		public:
			Adafruit_NeoPixel* strips[NUM_LED_STRIPS];
			uint8_t leftStrips[NUM_LED_STRIPS / 2] = {0, 1, 2, 3, 4};
			uint8_t rightStrips[NUM_LED_STRIPS / 2] = {5, 6, 7, 8, 9};

			//Adafruit_NeoMatrix* matrix;

			//MPU* mpus[NUM_MPUS];

			MPUCustom* mpus[NUM_MPUS];
			int mpu_addresses[2] = {0x68, 0x69};
			ActivationOrigin origins[2] = {ActivationOrigin::RightHand, ActivationOrigin::LeftHand};

		public:

			static Devices& getInstance() {
				static Devices instance; // Guaranteed to be destroyed and instantiated on first use.
				return instance;
    	}

			void initAll(){

				// LED STUFF

				strips[0] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_L_0, NEO_GRB + NEO_KHZ800);
				strips[1] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_L_1, NEO_GRB + NEO_KHZ800);
				strips[2] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_L_2, NEO_GRB + NEO_KHZ800);
				strips[3] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_L_3, NEO_GRB + NEO_KHZ800);
				strips[4] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_L_4, NEO_GRB + NEO_KHZ800);

				strips[5] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_R_0, NEO_GRB + NEO_KHZ800);
				strips[6] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_R_1, NEO_GRB + NEO_KHZ800);
				strips[7] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_R_2, NEO_GRB + NEO_KHZ800);
				strips[8] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_R_3, NEO_GRB + NEO_KHZ800);
				strips[9] = new Adafruit_NeoPixel(NUM_LEDS_PER_STRIP, STRIP_PIN_R_4, NEO_GRB + NEO_KHZ800);


				for(auto& strip : strips){
					strip->begin();
					strip->setBrightness(255);
					strip->clear();
					strip->show();
				}

				// SENSOR STUFF
				
				for(int i = 0; i < NUM_MPUS; i++){
					mpus[i]= new MPUCustom(Wire, mpu_addresses[i], origins[i]);
					mpus[i]->begin(2); // set value range to +/- [2, 4, 8, 16] g (note on provided number: 0->2g, 1->4g, 2->8g, 3->16g)
				}
				
			}

	unsigned long lastPrint = 0;
	unsigned long printInterval = 3000000;

	void updateSensors(){

		for(MPUCustom* mpu : mpus){
			mpu->update();

			
			if(micros() - lastPrint > printInterval){
				float ax = mpu->getAccX();
				float ay = mpu->getAccY();
				float az = mpu->getAccZ();
				float tot = mpu->getTotalAcc();
				float ws_tot = mpu->getWeaklySmoothedTotalAcc();
				float ss_tot = mpu->getStronglySmoothedTotalAcc();
				String printval = "id:" + String(mpu->mpu_addr) + ",ax:" + String(ax) + ",ay:" + String(ay) + ",az:" + String(az) + ",tot:" + String(tot) + ",ws_tot:" + String(ws_tot) + ",ss_tot:" + String(ss_tot);
				Serial.println(printval);
				lastPrint = micros();
			}
			
		}

	}

};
