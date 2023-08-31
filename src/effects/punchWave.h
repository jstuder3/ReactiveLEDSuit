#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class PunchWave : public Effect {

	public:
		Color color{255, 255, 255};
		uint8_t leftWaveUpdateSteps[NUM_LED_STRIPS][NUM_LEDS_PER_STRIP];
		uint8_t rightWaveUpdateSteps[NUM_LED_STRIPS][NUM_LEDS_PER_STRIP];

		const int armLength = 30;
		const int armLengthSquared = armLength * armLength;
		WaveOrigin origin;

		const float speed = 250.f;
		const float effectWidth = 10.f;

	public:

		PunchWave(WaveOrigin origin) : Effect("PunchWave"), origin(origin) {
			infiniteDuration = true;
			
			Serial.println("Starting PunchWave precomputation!");
			precomputeWave();
			Serial.println("PunchWave precomputation done!");	

			for(int i = 0; i < NUM_LEDS_PER_STRIP; i++){
				Serial.print(leftWaveUpdateSteps[0][i]);
				Serial.print(" - ");
			}
			Serial.println();

		}

		void update() override {

			//pointer to array of uint8_t
			uint8_t (*updateSteps)[NUM_LEDS_PER_STRIP];

			if(origin == WaveOrigin::RightHand){
				updateSteps = rightWaveUpdateSteps;
			}
			else{
				updateSteps = leftWaveUpdateSteps;
			}

			const float progress = fmod(((millis()-startTime) / 1000.f) * speed, NUM_LEDS_PER_STRIP + 200);

			for(int i = 0; i < NUM_LED_STRIPS; i++){
				for(int j = 0; j < NUM_LEDS_PER_STRIP; j++){
					const float distance = abs(progress - (float)updateSteps[i][j]);
					const float multiplier = pow(1.f - distance / effectWidth, 2);
					if(distance <= effectWidth){
						Devices::getInstance().strips[i]->setPixelColor(j, color.r * multiplier, color.g * multiplier, color.b * multiplier);
					}
				}
			}

		}

		/*
		*
		*/
		void precomputeWave(){

			// # LEFT #
			
			//pre-shoulder, left punch
			for(int i = 0; i <= armLength; i++){
				
				for(int j : Devices::getInstance().leftStrips)
					leftWaveUpdateSteps[j][i] = i; 

				for(int j : Devices::getInstance().rightStrips)
					leftWaveUpdateSteps[j][armLength - i] = armLength + i + NUM_LED_STRIPS / 2; //delay everything a bit so it looks like the wave "traverses" the torso

			}

			//post-shoulder / torso, left punch
			for(int i = 0; i < NUM_LEDS_PER_STRIP - armLength; i++){

				const int leftDistance = i + armLength;//floor(sqrt(i * i + armLengthSquared));
				const int rightDistance = (i+1) + armLength + NUM_LED_STRIPS / 2;//floor(sqrt((i+1) * (i+1) + armLengthSquared));

				for(int j : Devices::getInstance().leftStrips)
					leftWaveUpdateSteps[j][i + armLength] = leftDistance;

				for(int j : Devices::getInstance().rightStrips)
					leftWaveUpdateSteps[j][i + armLength] = rightDistance;

			}

			// # RIGHT #



		}

};