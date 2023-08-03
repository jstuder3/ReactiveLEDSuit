#include "effects/effect.h"
#include "other/utils.h"

class ConstantColor : public Effect {

	public:
		Color color{255, 255, 255};

	public:
		ConstantColor() : Effect("ConstantColor"), color(color) {};
		ConstantColor(Color color) : Effect("ConstantColor"), color(color) {}

		void update() override{

		}

};

