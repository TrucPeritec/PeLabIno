#ifndef __HHAL_PWM__
#define __HHAL_PWM__

#include "Arduino.h"
#include "HHAL.h"
#include "HHAL_PWM_Prop.h"
#include <ArduinoJson.h>

#define HHAL_PWM_COMMAND "PWM_COMMAND"
#define HHAL_PWM_READ_PROPERTIES "PWM_READ_PROPERTIES"
#define HHAL_PWM_WRITE_PROPERTIES "PWM_WRITE_PROPERTIES"
	#define HHAL_PWM_PIN "_pin"
	#define HHAL_PWM_VALUE "_value"


// #define HHAL_PWM_RESPONSE "RESPONSE"
#define HHAL_PWM_RESPONSE_NO_VALUE_TO_WRITE "NO VALUE TO WRITE"


class HHAL_PWM : HHAL
{
private:
	int8_t PWMInit();
	int8_t PWMDeinit();
	int8_t PWMWrite();

public:
	HHAL_PWM();

	virtual int8_t begin();
	virtual int8_t begin(uint8_t pin, uint16_t value);
	virtual int8_t end();
	virtual int8_t messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len);

	// setter -----------------------------
	virtual int8_t setProp(HHAL_Prop*);
	// setter -----------------------------

	//getter-------------------------------
	virtual HHAL_Prop* getProp();
	//getter-------------------------------

};


HHAL_PWM::HHAL_PWM()
{

}

int8_t HHAL_PWM::begin()
{
	if (_self_prop == NULL)
	{
		begin(HHAL_PWM_DEFAULT_PIN, HHAL_PWM_DEFAULT_VALUE);

		return 0;
	}

	return -1;
}

int8_t HHAL_PWM::begin(uint8_t pin, uint16_t value)
{
	if (_self_prop == NULL)
	{
		_self_prop = (HHAL_Prop*)(new HHAL_PWM_Prop);
		((HHAL_PWM_Prop*)_self_prop)->setPin(pin);
		((HHAL_PWM_Prop*)_self_prop)->setValue(value);

		PWMInit();
		PWMWrite();

		_self_prop->updateOccupied(1);

		return 0;
	}

	return -1;
}

int8_t HHAL_PWM::end()
{
	PWMDeinit();
	delete _self_prop;
}


int8_t HHAL_PWM::messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len)
{
	DynamicJsonDocument doc(MAX_JSON_DOC_SIZE);
	deserializeJson(doc, mess, mess_len);
	JsonObject json_object = doc.as<JsonObject>();

	DynamicJsonDocument res_doc(MAX_JSON_DOC_SIZE);

	if (json_object.containsKey(HHAL_PWM_COMMAND))
	{		
		if (json_object.containsKey(HHAL_PWM_PIN) && (doc[HHAL_PWM_PIN] == ((HHAL_PWM_Prop*)_self_prop)->getPin()))
		{
			char* command = doc[HHAL_PWM_COMMAND];

			if (!strcmp(command, HHAL_PWM_READ_PROPERTIES))
			{
				res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_OK;
				res_doc[HHAL_PWM_PIN] = ((HHAL_PWM_Prop*)_self_prop)->getPin();
				res_doc[HHAL_PWM_VALUE] = ((HHAL_PWM_Prop*)_self_prop)->getValue();

				serializeJson(res_doc, res, res_len);

				return 0;
			}
			else if(!strcmp(command, HHAL_PWM_WRITE_PROPERTIES))
			{
				if (json_object.containsKey(HHAL_PWM_VALUE))
				{
					uint16_t value = doc[HHAL_PWM_VALUE];
					((HHAL_PWM_Prop*)_self_prop)->setValue(value);

					PWMWrite();

					res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_OK;
					res_doc[HHAL_PWM_PIN] = ((HHAL_PWM_Prop*)_self_prop)->getPin();
					res_doc[HHAL_PWM_VALUE] = ((HHAL_PWM_Prop*)_self_prop)->getValue();

					serializeJson(res_doc, res, res_len);
					
					return 0;
				}
				else
				{
					res_doc[HHAL_RESPONSE] = HHAL_PWM_RESPONSE_NO_VALUE_TO_WRITE;
					serializeJson(res_doc, res, res_len);

					return -1;
				}
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

int8_t HHAL_PWM::PWMInit()
{
	uint8_t pin = ((HHAL_PWM_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	pinMode(pin, OUTPUT);
	// Hardware dependence--------------------------------------

	return 0;
}

int8_t HHAL_PWMPWMDeinit()
{
	uint8_t pin = ((HHAL_PWM_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	pinMode(pin, INPUT);
	// Hardware dependence--------------------------------------

	return 0;
}

int8_t HHAL_PWM::PWMWrite()
{
	uint8_t pin = ((HHAL_PWM_Prop*)_self_prop)->getPin();
	uint16_t value = ((HHAL_PWM_Prop*)_self_prop)->getValue();

	// Hardware dependence--------------------------------------
	analogWrite(pin, value);
	// Hardware dependence--------------------------------------

	return 0;
}
 

// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_PWM::setProp(HHAL_Prop* prop)
{
	*((HHAL_PWM_Prop*)_self_prop) = *((HHAL_PWM_Prop*)prop);

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
HHAL_Prop* HHAL_PWM::getProp()
{
	return _self_prop;
}
// getter -----------------------------------------------------------------------------------------------

#endif