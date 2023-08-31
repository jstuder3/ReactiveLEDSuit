/* 
 * 
 * Adapted from MPU6050_Light library found here: https://github.com/rfetick/MPU6050_light
 *              
 */

#include "MPUCustom.h"
#include "Arduino.h"

/* INIT and BASIC FUNCTIONS */

MPUCustom::MPUCustom(TwoWire &w, int mpu_addr) : wire(&w), mpu_addr(mpu_addr) {}

byte MPUCustom::begin(int acc_config_num){
  writeData(MPU6050_SMPLRT_DIV_REGISTER, 0x00);
  writeData(MPU6050_CONFIG_REGISTER, 0x00);
  setAccConfig(acc_config_num);
  byte status = writeData(MPU6050_PWR_MGMT_1_REGISTER, 0x01); // check only the last connection with status
  
  this->update();
  return status;
}

byte MPUCustom::writeData(byte reg, byte data){
  wire->beginTransmission(mpu_addr);
  wire->write(reg);
  wire->write(data);
  byte status = wire->endTransmission();
  return status; // 0 if success
}

/* SETTER */

byte MPUCustom::setAccConfig(int config_num){
    byte status;
    switch(config_num){
        case 0: // range = +- 2 g
        acc_divisor = 16384.0;
        status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x00);
        break;
        case 1: // range = +- 4 g
        acc_divisor = 8192.0;
        status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x08);
        break;
        case 2: // range = +- 8 g
        acc_divisor = 4096.0;
        status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x10);
        break;
        case 3: // range = +- 16 g
        acc_divisor = 2048.0;
        status = writeData(MPU6050_ACCEL_CONFIG_REGISTER, 0x18);
        break;
        default: // error
        status = 1;
        break;
    }
    return status;
}

/* UPDATE */

void MPUCustom::update(){
    // retrieve raw data
    wire->beginTransmission(mpu_addr);
    wire->write(MPU6050_ACCEL_OUT_REGISTER);
    wire->endTransmission(false);
    wire->requestFrom((int)mpu_addr, 6);

    int16_t rawData[3]; // [ax,ay,az,temp,gx,gy,gz]

    for(int i=0;i<3;i++){
        rawData[i]  = wire->read() << 8;
        rawData[i] |= wire->read();
    }

    accX = rawData[0] / acc_divisor;
    accY = rawData[1] / acc_divisor;
    accZ = rawData[2] / acc_divisor;
    
    totalAcc = sqrt(sq(accX) + sq(accY) + sq(accZ));

    weaklySmoothedTotalAcc = WEAK_SMOOTHING_ALPHA * weaklySmoothedTotalAcc + (1.f - WEAK_SMOOTHING_ALPHA) * totalAcc;
    stronglySmoothedTotalAcc = STRONG_SMOOTHING_ALPHA * stronglySmoothedTotalAcc + (1.f - STRONG_SMOOTHING_ALPHA) * totalAcc;

} 
