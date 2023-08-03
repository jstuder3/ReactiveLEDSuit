#include <Arduino.h>
#include "effects/effect.h"

#pragma once
#define MAX_EFFECTS 10

class EffectController{

	public:
		Effect* effects[MAX_EFFECTS];

	public:

	  // Static method for access to class instance
    static EffectController& getInstance() {
        static EffectController instance; // Guaranteed to be destroyed and instantiated on first use.
        return instance;
    }

		void update();
		void clearAll();
		void showAll();
		bool registerEffect(Effect* effect);

	private:
		// Private Constructor
		EffectController(){};
		// Prevent copy constructor and assignment operator
    EffectController(const EffectController&) = delete;  // No copy constructor
    EffectController& operator=(const EffectController&) = delete;  // No assignment operator

};
