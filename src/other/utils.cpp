#include "other/utils.h"

Color Utils::intToColor(int val)
{
	Color rgbColor;

	if (val < 85)
	{
		rgbColor.r = 255 - val * 3;
		rgbColor.g = val * 3;
		rgbColor.b = 0;
	}
	else if (val < 170)
	{
		val -= 85;
		rgbColor.r = 0;
		rgbColor.g = 255 - val * 3;
		rgbColor.b = val * 3;
	}
	else
	{
		val -= 170;
		rgbColor.r = val * 3;
		rgbColor.g = 0;
		rgbColor.b = 255 - val * 3;
	}

	return rgbColor;
}

