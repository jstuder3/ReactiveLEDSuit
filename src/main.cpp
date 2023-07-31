#include <Arduino.h>

#include "other/utils.h"
#include "controllers/effectController.h"
#include "controllers/inputController.h"
#include "devices.h"

void setup()
{
	Serial.begin(9600);
	Serial.flush();

	Devices::getInstance().initAll();
}

void loop()
{
	InputController::getInstance().update();
	EffectController::getInstance().update();

	delay(50);
}
