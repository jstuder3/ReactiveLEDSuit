#include "effects/effect.h"
#include "other/utils.h"

class ConstantColor : public Effect {

	public:
		Color constantColor;

	public:
		ConstantColor(Device device, MixingMode mixingMode, Color constantColor) : Effect(device, "ConstantColor", mixingMode), constantColor(constantColor) {}

};

