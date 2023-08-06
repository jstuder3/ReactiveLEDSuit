#pragma once

#include <Arduino.h>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

enum Device{
	strips,
	matrix
};

enum MixingMode {
	Additive,
	Multiplicative
};

enum WaveOrigin{
	RightHand,
	LeftHand,
	RightFoot,
	LeftFoot
};

enum PlayDirection{
	Forward,
	Backward
};

class Utils {

	public:
		static Color intToColor(int val);

};
