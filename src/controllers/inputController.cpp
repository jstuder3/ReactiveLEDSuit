#include "controllers/inputController.h"
#include "devices.h"
#include "effectController.h"
#include "effects/punchWave.h"
#include "effects/blinking.h"
#include "effects/scanWave.h"
#include "effects/rainbow.h"

#pragma once

void InputController::update(){

    pinMode(GPIO_NUM_4, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_12, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_2, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_15, INPUT_PULLDOWN);


    if(digitalRead(GPIO_NUM_4) == HIGH){
        Serial.println("Button 1 pressed. Cleared all current effects.");
        EffectController::getInstance().killAllEffects();
    }
    if(digitalRead(GPIO_NUM_12) == HIGH){
        Serial.println("Button 2 pressed. Blinking on all strips.");
        EffectController::getInstance().killAllEffects();
        for(int i = 0; i < NUM_LED_STRIPS; i++){
		    EffectController::getInstance().registerEffect(new Blinking(Devices::getInstance().strips[i]));
	    }
    }
    if(digitalRead(GPIO_NUM_2) == HIGH){
        Serial.println("Button 3 pressed. Scannwave on all strips.");
        
        EffectController::getInstance().killAllEffects();
        
        EffectConfiguration config = EffectConfiguration();
        config.strip = Devices::getInstance().strips[0];
        for(int i = 0; i < NUM_LED_STRIPS; i++){
            config.strip = Devices::getInstance().strips[i];
            config.startTimeOffset = i * 1000UL; //random(0UL, 0);
            EffectController::getInstance().registerEffect(new ScanWave(config));
        }
    }
    if(digitalRead(GPIO_NUM_15) == HIGH){
        Serial.println("Button 4 pressed. Rainbow on all strips.");
        EffectController::getInstance().killAllEffects();
        for(int i = 0; i < NUM_LED_STRIPS; i++){
            EffectController::getInstance().registerEffect(new Rainbow(Devices::getInstance().strips[i]));
        }
    }

    for(int i = 0; i < NUM_MPUS; i++){
        MPUCustom* mpu = Devices::getInstance().mpus[i];
        float ws_tot = mpu->getWeaklySmoothedTotalAcc();

        if(ws_tot > 5.f){
            if(millis() - lastActivation[i] > activationCooldown){
                Serial.print("MPU ");
                Serial.print(i);
                Serial.println(" activated");
                lastActivation[i] = millis();

                EffectController::getInstance().registerEffect(new PunchWave(mpu->getActivationOrigin()));
                
            }
        }
    }
    
}
