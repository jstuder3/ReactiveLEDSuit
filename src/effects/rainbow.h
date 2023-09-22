#include <math.h>
#include <Arduino.h>
#include "effect.h"
#include "other/utils.h"
#include <Adafruit_NeoPixel.h>
#include "devices.h"

class Rainbow : public Effect {

	public:
		const float speed = 0.5f;
        const int maxBrightness = 100;

	public:
		Rainbow(Adafruit_NeoPixel* strip) : Effect("Rainbow", strip) {
            infiniteDuration = true;
		}

		void update() override {
            //Serial.println("Updated Rainbow from strip " + String(strip->getPin()));
			for(int i = 0; i < strip->numPixels(); i++){
                float hue = fmod((float)(millis()/1000.f * speed) + (float)i / strip->numPixels(), 1.f);
                Color color = HSVtoRGB(HSV{hue * 360.f, 1.f, 1.f});
                color.r *= maxBrightness / 255.f;
                color.g *= maxBrightness / 255.f;
                color.b *= maxBrightness / 255.f;
                strip->setPixelColor(i, color.r, color.g, color.b);
            }
		}

    Color HSVtoRGB(HSV hsv) {
        Color rgb;
        float hh, p, q, t, ff;
        long i;

        if(hsv.s <= 0.0) {       // < is bogus, just shuts up warnings
            rgb.r = hsv.v * 255.0;
            rgb.g = hsv.v * 255.0;
            rgb.b = hsv.v * 255.0;
            return rgb;
        }
    
        hh = hsv.h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = hsv.v * (1.0 - hsv.s);
        q = hsv.v * (1.0 - (hsv.s * ff));
        t = hsv.v * (1.0 - (hsv.s * (1.0 - ff)));

        switch(i) {
        case 0:
            rgb.r = hsv.v * 255.0;
            rgb.g = t * 255.0;
            rgb.b = p * 255.0;
            break;
        case 1:
            rgb.r = q * 255.0;
            rgb.g = hsv.v * 255.0;
            rgb.b = p * 255.0;
            break;
        case 2:
            rgb.r = p * 255.0;
            rgb.g = hsv.v * 255.0;
            rgb.b = t * 255.0;
            break;
        case 3:
            rgb.r = p * 255.0;
            rgb.g = q * 255.0;
            rgb.b = hsv.v * 255.0;
            break;
        case 4:
            rgb.r = t * 255.0;
            rgb.g = p * 255.0;
            rgb.b = hsv.v * 255.0;
            break;
        case 5:
        default:
            rgb.r = hsv.v * 255.0;
            rgb.g = p * 255.0;
            rgb.b = q * 255.0;
            break;
        }

        return rgb;
    }

};
