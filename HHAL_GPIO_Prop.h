#ifndef __HHAL_GPIO_PROP__
#define __HHAL_GPIO_PROP__

#include "Arduino.h"
#include "HHAL_Prop.h"


#define HHAL_GPIO_INPUT_MODE INPUT // 0
#define HHAL_GPIO_OUTPUT_MODE OUTPUT // 1
#define HHAL_GPIO_INPUT_PULLUP_MODE INPUT_PULLUP // 2

#define HHAL_GPIO_DEFAULT_PIN LED_BUILTIN
#define HHAL_GPIO_DEFAULT_MODE HHAL_GPIO_INPUT_MODE
#define HHAL_GPIO_DEFAULT_STATE LOW

class HHAL_GPIO_Prop : HHAL_Prop
{
private:
	uint8_t _pin;
	uint8_t _mode;
	bool _state;

public:
	HHAL_GPIO_Prop();

	// setter -----------------------------
	int8_t setPin(uint8_t);
	int8_t setMode(uint8_t);
	int8_t setState(bool);
	// setter -----------------------------

	//getter-------------------------------
	uint8_t getPin();
	uint8_t getMode();
	bool getState();
	//getter-------------------------------
};


HHAL_GPIO_Prop::HHAL_GPIO_Prop()
{
	_pin = HHAL_GPIO_DEFAULT_PIN;
	_mode = HHAL_GPIO_DEFAULT_MODE;
	_state = HHAL_GPIO_DEFAULT_STATE;
}


// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_GPIO_Prop::setPin(uint8_t pin)
{
	_pin = pin;

	return 0;
}

int8_t HHAL_GPIO_Prop::setMode(uint8_t mode)
{
	_mode = mode;

	return 0;
}

int8_t HHAL_GPIO_Prop::setState(bool state)
{
	_state = state;

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
uint8_t HHAL_GPIO_Prop::getPin()
{
	return _pin;
}

uint8_t HHAL_GPIO_Prop::getMode()
{
	return _mode;
}

bool HHAL_GPIO_Prop::getState()
{
	return _state;
}
// getter -----------------------------------------------------------------------------------------------

#endif