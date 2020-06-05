#ifndef __HHAL_PWM_PROP__
#define __HHAL_PWM_PROP__

#include "Arduino.h"
#include "HHAL_Prop.h"

#define HHAL_PWM_DEFAULT_PIN 5
#define HHAL_PWM_DEFAULT_VALUE 0

class HHAL_PWM_Prop : HHAL_Prop
{
private:
	uint8_t _pin;
	uint16_t _value;

public:
	HHAL_PWM_Prop();

	// setter -----------------------------
	int8_t setPin(uint8_t);
	int8_t setValue(uint16_t);
	// setter -----------------------------

	//getter-------------------------------
	uint8_t getPin();
	uint16_t getValue();
	//getter-------------------------------
};


HHAL_PWM_Prop::HHAL_PWM_Prop()
{
	_pin = HHAL_PWM_DEFAULT_PIN;
	_value = HHAL_PWM_DEFAULT_VALUE;
}


// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_PWM_Prop::setPin(uint8_t pin)
{
	_pin = pin;

	return 0;
}

int8_t HHAL_PWM_Prop::setValue(uint16_t value)
{
	_value = value;

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
uint8_t HHAL_PWM_Prop::getPin()
{
	return _pin;
}

uint16_t HHAL_PWM_Prop::getValue()
{
	return _value;
}
// getter -----------------------------------------------------------------------------------------------

#endif