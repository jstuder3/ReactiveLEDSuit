#pragma once

#include <Arduino.h>

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct HSV {
    float h; // Angle in degrees [0,360]
    float s; // Percent [0,1]
    float v; // Percent [0,1]
};

enum Device{
	strips,
	matrix
};

enum MixingMode {
	Additive,
	Multiplicative
};

enum ActivationOrigin{
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
