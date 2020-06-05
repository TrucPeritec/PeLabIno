#ifndef __HHAL_ANALOG__
#define __HHAL_ANALOG__

#include "Arduino.h"
#include "HHAL.h"
#include "HHAL_Analog_Prop.h"
#include <ArduinoJson.h>

#define HHAL_ANALOG_COMMAND "ANALOG_COMMAND"
#define HHAL_ANALOG_READ_PROPERTIES "ANALOG_READ_PROPERTIES"
	#define HHAL_ANALOG_PIN "_pin"
	#define HHAL_ANALOG_VALUE "_value"


// #define HHAL_ANALOG_RESPONSE "RESPONSE"


class HHAL_Analog : HHAL
{
private:
	int8_t analogInit();
	int8_t analogDeinit();
	uint32_t analogRead();

public:
	HHAL_Analog();

	virtual int8_t begin();
	virtual int8_t begin(uint8_t pin);
	virtual int8_t end();
	virtual int8_t messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len);

	// setter -----------------------------
	virtual int8_t setProp(HHAL_Prop*);
	// setter -----------------------------

	//getter-------------------------------
	virtual HHAL_Prop* getProp();
	//getter-------------------------------

};


HHAL_Analog::HHAL_Analog()
{

}

int8_t HHAL_Analog::begin()
{
	if (_self_prop == NULL)
	{
		begin(HHAL_ANALOG_DEFAULT_PIN);

		return 0;
	}

	return -1;
}

int8_t HHAL_Analog::begin(uint8_t pin)
{
	if (_self_prop == NULL)
	{
		_self_prop = (HHAL_Prop*)(new HHAL_Analog_Prop);
		((HHAL_Analog_Prop*)_self_prop)->setPin(pin);

		analogInit();

		_self_prop->updateOccupied(1);

		return 0;
	}

	return -1;
}

int8_t HHAL_Analog::end()
{
	analogDeinit();
	delete _self_prop;
}


int8_t HHAL_Analog::messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len)
{
	DynamicJsonDocument doc(MAX_JSON_DOC_SIZE);
	deserializeJson(doc, mess, mess_len);
	JsonObject json_object = doc.as<JsonObject>();

	DynamicJsonDocument res_doc(MAX_JSON_DOC_SIZE);

	if (json_object.containsKey(HHAL_ANALOG_COMMAND))
	{		
		if (json_object.containsKey(HHAL_ANALOG_PIN) && (doc[HHAL_ANALOG_PIN] == ((HHAL_Analog_Prop*)_self_prop)->getPin()))
		{
			char* command = doc[HHAL_ANALOG_COMMAND];

			if (!strcmp(command, HHAL_ANALOG_READ_PROPERTIES))
			{
				res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_OK;
				res_doc[HHAL_ANALOG_PIN] = ((HHAL_Analog_Prop*)_self_prop)->getPin();
				res_doc[HHAL_ANALOG_VALUE] = analogRead();

				serializeJson(res_doc, res, res_len);

				return 0;
			}
			else
			{
				// res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_INVAILED_COMMAND;
				// serializeJson(res_doc, res, res_len);

				return -2;
			}	
		}	
	}
	else
	{
		// res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_NO_COMMAND;
		// serializeJson(res_doc, res, res_len);

		return -3;
	}

	return -4;
}

int8_t HHAL_Analog::analogInit()
{
	uint8_t pin = ((HHAL_Analog_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	pinMode(pin, INPUT);
	// Hardware dependence--------------------------------------

	return 0;
}

int8_t HHAL_Analog::analogDeinit()
{
	uint8_t pin = ((HHAL_Analog_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	pinMode(pin, INPUT);
	// Hardware dependence--------------------------------------

	return 0;
}

uint32_t HHAL_Analog::analogRead()
{
	uint8_t pin = ((HHAL_Analog_Prop*)_self_prop)->getPin();

	return ::analogRead(pin);
}

// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_Analog::setProp(HHAL_Prop* prop)
{
	*((HHAL_Analog_Prop*)_self_prop) = *((HHAL_Analog_Prop*)prop);

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
HHAL_Prop* HHAL_Analog::getProp()
{
	return _self_prop;
}
// getter -----------------------------------------------------------------------------------------------

#endif