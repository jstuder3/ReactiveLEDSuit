/*
#include <Arduino.h>

#include <Wire.h>

class Sensors{
	private:
		float minVal = 9999;
		float maxVal = -9999;

		float gravity[3];
		const float alpha = 0.8;
		MPU6050* mpu;

	public:
		Sensors();
		void update();
		void updateGravity(float ax, float ay, float az);
};
*/