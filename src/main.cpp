#include <Arduino.h>

#include "other/utils.h"
#include "controllers/effectController.h"
#include "controllers/inputController.h"
#include "devices.h"
//#include "effects/effect.h"
#include "effects/blinking.h"
#include "effects/scanWave.h"
#include "effects/punchWave.h"
#include <Wire.h>

float avgLoopDuration = 1.f;
const float alpha = 0.95f;

const bool printTimingInfo = false;
unsigned long loopStart;

int mpu_addr = 0x68;

void setup()
{
	Wire.begin();
	Wire.setClock(400000UL); // Set I2C frequency to 400kHz
	
	Serial.begin(115200);
	Serial.flush();

	Devices::getInstance().initAll();

	//EffectController::getInstance().registerEffect(new PunchWave(WaveOrigin::Left));

	EffectConfiguration config = EffectConfiguration();

	config.strip = Devices::getInstance().strips[0];
	for(int i = 0; i < 5; i++){
		config.startTimeOffset = i * 1000UL; //random(0UL, 0);
		EffectController::getInstance().registerEffect(new ScanWave(config));
	}

	config.strip = Devices::getInstance().strips[2];
	for(int i = 0; i < 5; i++){
		config.startTimeOffset = i * 1000UL; //random(0UL, 20000UL);
		EffectController::getInstance().registerEffect(new ScanWave(config));
	}

	/*EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));
	delay(200);
	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));*/

	/*delay(200);
	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[0]));
	delay(400);
	EffectController::getInstance().registerEffect(new ScanWave(Devices::getInstance().strips[1]));
	delay(2000);
	EffectController::getInstance().registerEffect(new ScanWave(Devices::getInstance().strips[1]));


	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));
	delay(200);
	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));
*/

}

void loop()
{
	if(printTimingInfo){
		loopStart = millis();
	}

	InputController::getInstance().update();
	EffectController::getInstance().update();

	if(printTimingInfo){
		float loopDuration = (millis() - loopStart);
		avgLoopDuration = alpha * avgLoopDuration + (1.f-alpha) * loopDuration;
		if(millis() % 20 == 0){
			Serial.print("Possible updates per second: ");
			Serial.println(1000.f/avgLoopDuration);
		}
	}
/*
	Serial.println("X: " + Devices::getInstance().getAccelX(mpu_addr));
	Serial.println("Y: " + Devices::getInstance().getAccelY(mpu_addr));
	Serial.println("Z: " + Devices::getInstance().getAccelZ(mpu_addr));
	Serial.println();
	Serial.println("---------------------------------");

	Serial.println();

	delay(50);*/

}
