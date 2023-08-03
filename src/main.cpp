#include <Arduino.h>

#include "other/utils.h"
#include "controllers/effectController.h"
#include "controllers/inputController.h"
#include "devices.h"
//#include "effects/effect.h"
#include "effects/blinking.h"
#include "effects/scanWave.h"

float avgLoopDuration = 0.0f;
const float alpha = 0.95f;

void setup()
{
	Serial.begin(9600);
	Serial.flush();

	Devices::getInstance().initAll();

	EffectController::getInstance().registerEffect(new ScanWave(Devices::getInstance().strips[0]));
	delay(2000);
	EffectController::getInstance().registerEffect(new ScanWave(Devices::getInstance().strips[0]));
	delay(2000);
	EffectController::getInstance().registerEffect(new ScanWave(Devices::getInstance().strips[0]));


	/*EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));
	delay(200);
	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[1]));*/

	/*delay(200);
	EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[0]));
	/*delay(400);
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
	unsigned long loopStart = millis();

	InputController::getInstance().update();
	EffectController::getInstance().update();

	float loopDuration = (millis() - loopStart);
	avgLoopDuration = alpha * avgLoopDuration + (1.f-alpha) * loopDuration;
	Serial.print("Possible updates per second: ");
	Serial.println(1000.f/avgLoopDuration);

}
