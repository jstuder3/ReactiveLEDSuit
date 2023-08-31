#include <Arduino.h>
#include "devices.h"

#pragma once

class InputController {
	public:
    int lastActivation[NUM_MPUS];
    int activationCooldown = 1000;

public:
		// Static method for access to class instance
    static InputController& getInstance() {
        static InputController instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

		void update();
    /*{
			//Serial.println("Updated InputController");
		};*/


	private:
		// Private Constructor
    InputController() {};
    // Prevent copy constructor and assignment operator
    InputController(const InputController&) = delete;  // No copy constructor
    InputController& operator=(const InputController&) = delete;  // No assignment operator

};
