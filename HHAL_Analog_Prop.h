#ifndef __HHAL_ANALOG_PROP__
#define __HHAL_ANALOG_PROP__

#include "Arduino.h"
#include "HHAL_Prop.h"

#define HHAL_ANALOG_DEFAULT_PIN A0

class HHAL_Analog_Prop : HHAL_Prop
{
private:
	uint8_t _pin;

public:
	HHAL_Analog_Prop();

	// setter -----------------------------
	int8_t setPin(uint8_t);
	// setter -----------------------------

	//getter-------------------------------
	uint8_t getPin();
	//getter-------------------------------
};


HHAL_Analog_Prop::HHAL_Analog_Prop()
{
	_pin = HHAL_ANALOG_DEFAULT_PIN;
}


// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_Analog_Prop::setPin(uint8_t pin)
{
	_pin = pin;

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
uint8_t HHAL_Analog_Prop::getPin()
{
	return _pin;
}
// getter -----------------------------------------------------------------------------------------------

#endif