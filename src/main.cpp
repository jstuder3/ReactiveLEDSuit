#include <Arduino.h>

#include "other/utils.h"
#include "controllers/effectController.h"
#include "controllers/inputController.h"

InputController inputController;
EffectController effectController;

void setup()
{
	Serial.begin(9600);
	Serial.flush();
}

void loop()
{
	inputController.update();
	effectController.update();

	delay(50);
}
