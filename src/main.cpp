#include <Arduino.h>

#include <Wire.h>
#include <MPU6050_light.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6  // Set to the pin where your strip is connected
#define NUM_LEDS   150 // Set to the number of LEDs on your strip

float gravity[3];
const float alpha = 0.8;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

MPU6050 mpu(Wire);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int colors[NUM_LEDS];
float minVal = 9999;
float maxVal = -9999;

void setup()
{
  Serial.begin(9600);
  Serial.flush();
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Wire.begin();
  mpu.begin();
  Serial.println(F("Calculating gyro offset, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true, true);
  Serial.println("Done.");
}


void advanceOneStep(){
  for(int i = strip.numPixels(); i >= 1; i--){
      colors[i] = colors[i-1];
  }
  colors[0] = 0;
}

Color intToColor(int val) {
  Color rgbColor;
  
  if (val < 85) {
    rgbColor.r = 255 - val * 3;
    rgbColor.g = val * 3;
    rgbColor.b = 0;
  } else if (val < 170) {
    val -= 85;
    rgbColor.r = 0;
    rgbColor.g = 255 - val * 3;
    rgbColor.b = val * 3;
  } else {
    val -= 170;
    rgbColor.r = val * 3;
    rgbColor.g = 0;
    rgbColor.b = 255 - val * 3;
  }

  return rgbColor;
}
void setColors(){
  for(int i = 0; i < strip.numPixels(); i++){
    Color col = intToColor(colors[i]);
    //strip.setPixelColor(i, col.r, col.g, col.b);
    //strip.setPixelColor(i, col.b, col.b, col.b);
    const int val = colors[i] > 200 ? 255 : 0;
    strip.setPixelColor(i, val, val, val);
  }
  strip.show();
}

void updateGravity(float ax, float ay, float az){

  gravity[0] = alpha * gravity[0] + (1 - alpha) * ax;
  gravity[1] = alpha * gravity[1] + (1 - alpha) * ay;
  gravity[2] = alpha * gravity[2] + (1 - alpha) * az;

}

void loop()
{
    mpu.update();

    float ax = mpu.getAccX();
    float ay = mpu.getAccY();
    float az = mpu.getAccZ();

    updateGravity(ax, ay, az);

    ax -= gravity[0];
    ay -= gravity[1];
    az -= gravity[2];

    float total = sqrt(sq(ax) + sq(ay) + sq(az));

    if(total > maxVal){
      maxVal = total;
    }
    if(total < minVal){
      minVal = total;
    }

    //Serial.print("X:" + String(ax));
    //Serial.print("\tY:" + String(ay));
    //Serial.print("\tZ:" + String(az));
    //Serial.print("\tTotal:" + String(total));
    //Serial.print("\tMin:" + String(minVal));
    //Serial.print("\tMax:" + String(maxVal));
    //Serial.print("\tG0:" + String(gravity[0]));
    //Serial.print("\tG1:" + String(gravity[1]));
    //Serial.print("\tG2:" + String(gravity[2]));

    total -=minVal;
    total /= (maxVal-minVal);

    advanceOneStep();

    colors[0] = uint8_t(255 * total);

    setColors();

    //Serial.print("\tAdjusted_value:" + String(uint8_t(255 * total)));

    //Serial.println();

//    colors[0] = constrain(x, 0, 255);

    //delay(5);
}
