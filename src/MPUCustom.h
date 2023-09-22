/* 
 * 
 * Adapted from MPU6050_Light library found here: https://github.com/rfetick/MPU6050_light
 *              
 */

/* The register map is provided at
 * https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] °/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(°/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81m/s²)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/


#include "Arduino.h"
#include "Wire.h"
#include "other/utils.h"

#define MPU6050_SMPLRT_DIV_REGISTER   0x19
#define MPU6050_CONFIG_REGISTER       0x1a
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1c
#define MPU6050_PWR_MGMT_1_REGISTER   0x6b

#define MPU6050_GYRO_OUT_REGISTER     0x43
#define MPU6050_ACCEL_OUT_REGISTER    0x3B

#define WEAK_SMOOTHING_ALPHA 0.7f
#define STRONG_SMOOTHING_ALPHA 0.9f

class MPUCustom{
  public:
    // INIT and BASIC FUNCTIONS
	MPUCustom(TwoWire &w, int mpu_addr, ActivationOrigin activationOrigin) : wire(&w), mpu_addr(mpu_addr), activationOrigin(activationOrigin) {};
    byte begin(int acc_config_num=0);
	
	byte writeData(byte reg, byte data);
	
	// MPU CONFIG SETTER
	byte setAccConfig(int config_num);
	
	// INLOOP GETTER

    float getAccX(){ return accX; };
    float getAccY(){ return accY; };
    float getAccZ(){ return accZ; };
    float getTotalAcc() { return totalAcc; };
    float getWeaklySmoothedTotalAcc() { return weaklySmoothedTotalAcc; };
    float getStronglySmoothedTotalAcc() { return stronglySmoothedTotalAcc; };
    ActivationOrigin getActivationOrigin() { return activationOrigin; };

	// INLOOP UPDATE
    void update();

    int mpu_addr;

  private:
    TwoWire *wire;
	float acc_divisor;
    float accX, accY, accZ, totalAcc;
    float weaklySmoothedTotalAcc, stronglySmoothedTotalAcc;
    ActivationOrigin activationOrigin;
};
