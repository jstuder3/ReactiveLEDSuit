#include "controllers/inputController.h"
#include "devices.h"

void InputController::update(){

    Devices::getInstance().updateSensors();

    for(int i = 0; i < NUM_MPUS; i++){
        MPUCustom* mpu = Devices::getInstance().mpus[i];
        float ws_tot = mpu->getWeaklySmoothedTotalAcc();

        if(ws_tot > 5.f){
            if(millis() - lastActivation[i] > activationCooldown){
                Serial.print("MPU ");
                Serial.print(i);
                Serial.println(" activated");
                lastActivation[i] = millis();

                
                
            }
        }
    }
    
}
