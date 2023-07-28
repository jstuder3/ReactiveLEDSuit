#include "other/utils.h"

class Effect{

	protected:
		Device device;
		String name;
		MixingMode mixingMode;
		unsigned long startTime;
		unsigned long endTime;

	public:
		Effect();
		Effect(Device device, String name, MixingMode mixingMode) : device(device), name(name), mixingMode(mixingMode) {};
		void update(unsigned long currentTime);

		bool isExpired(unsigned long currentTime){
			return currentTime > endTime;
		}

};
