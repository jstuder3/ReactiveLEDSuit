#include <Arduino.h>

#pragma once

class InputController {
	public:

		// Static method for access to class instance
    static InputController& getInstance() {
        static InputController instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

		void update(){
			//Serial.println("Updated InputController");
		};

	private:
		// Private Constructor
    InputController() {};
    // Prevent copy constructor and assignment operator
    InputController(const InputController&) = delete;  // No copy constructor
    InputController& operator=(const InputController&) = delete;  // No assignment operator


};
