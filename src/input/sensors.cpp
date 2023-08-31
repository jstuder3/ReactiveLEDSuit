/*#include <Arduino.h>
#include "input/sensors.h"

#include <Wire.h>

Sensors::Sensors(){
    Wire.begin();
		mpu = new MPU6050(Wire);
    mpu->begin();
    Serial.println(F("Calculating gyro offset, do not move MPU6050"));
    delay(1000);
    mpu->calcOffsets(true, true);
    Serial.println("Done.");
}

void Sensors::update(){
	mpu->update();

	float ax = mpu->getAccX();
	float ay = mpu->getAccY();
	float az = mpu->getAccZ();

	updateGravity(ax, ay, az);

	ax -= gravity[0];
	ay -= gravity[1];
	az -= gravity[2];

	float total = sqrt(sq(ax) + sq(ay) + sq(az));

	if (total > maxVal)
	{
		maxVal = total;
	}
	if (total < minVal)
	{
		minVal = total;
	}

	// Serial.print("X:" + String(ax));
	// Serial.print("\tY:" + String(ay));
	// Serial.print("\tZ:" + String(az));
	// Serial.print("\tTotal:" + String(total));
	// Serial.print("\tMin:" + String(minVal));
	// Serial.print("\tMax:" + String(maxVal));
	// Serial.print("\tG0:" + String(gravity[0]));
	// Serial.print("\tG1:" + String(gravity[1]));
	// Serial.print("\tG2:" + String(gravity[2]));

	total -= minVal;
	total /= (maxVal - minVal);
}

void Sensors::updateGravity(float ax, float ay, float az)
{

	gravity[0] = alpha * gravity[0] + (1 - alpha) * ax;
	gravity[1] = alpha * gravity[1] + (1 - alpha) * ay;
	gravity[2] = alpha * gravity[2] + (1 - alpha) * az;
}
*/