#ifndef __HHAL_GPIO__
#define __HHAL_GPIO__

#include "Arduino.h"
#include "HHAL.h"
#include "HHAL_GPIO_Prop.h"
#include <ArduinoJson.h>

#define HHAL_GPIO_COMMAND "GPIO_COMMAND"
#define HHAL_GPIO_READ_PROPERTIES "GPIO_READ_PROPERTIES"
#define HHAL_GPIO_WRITE_PROPERTIES "GPIO_WRITE_PROPERTIES"
	#define HHAL_GPIO_PIN "_pin"
	#define HHAL_GPIO_MODE "_mode"
	#define HHAL_GPIO_STATE "_state"


// #define HHAL_GPIO_RESPONSE "RESPONSE"
#define HHAL_GPIO_RESPONSE_NO_VALUE_TO_WRITE "NO VALUE TO WRITE"


class HHAL_GPIO : HHAL
{
private:
	int8_t GPIOInit();
	int8_t GPIODeinit();
	bool GPIORead();
	int8_t GPIOWrite();

public:
	HHAL_GPIO();

	virtual int8_t begin();
	virtual int8_t begin(uint8_t pin, uint8_t mode, bool state);
	virtual int8_t end();
	virtual int8_t messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len);

	// setter -----------------------------
	virtual int8_t setProp(HHAL_Prop*);
	// setter -----------------------------

	//getter-------------------------------
	virtual HHAL_Prop* getProp();
	//getter-------------------------------

};


HHAL_GPIO::HHAL_GPIO()
{

}

int8_t HHAL_GPIO::begin()
{
	if (_self_prop == NULL)
	{
		begin(HHAL_GPIO_DEFAULT_PIN, HHAL_GPIO_DEFAULT_MODE, HHAL_GPIO_DEFAULT_STATE);

		return 0;
	}

	return -1;
}

int8_t HHAL_GPIO::begin(uint8_t pin, uint8_t mode, bool state)
{
	if (_self_prop == NULL)
	{
		_self_prop = (HHAL_Prop*)(new HHAL_GPIO_Prop);
		((HHAL_GPIO_Prop*)_self_prop)->setPin(pin);
		((HHAL_GPIO_Prop*)_self_prop)->setMode(mode);
		((HHAL_GPIO_Prop*)_self_prop)->setState(state);

		GPIOInit();

		_self_prop->updateOccupied(1);

		return 0;
	}

	return -1;
}

int8_t HHAL_GPIO::end()
{
	GPIODeinit();
	delete _self_prop;
}


int8_t HHAL_GPIO::messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len)
{
	DynamicJsonDocument doc(MAX_JSON_DOC_SIZE);
	deserializeJson(doc, mess, mess_len);
	JsonObject json_object = doc.as<JsonObject>();

	DynamicJsonDocument res_doc(MAX_JSON_DOC_SIZE);

	if (json_object.containsKey(HHAL_GPIO_COMMAND))
	{		
		if (json_object.containsKey(HHAL_GPIO_PIN) && (doc[HHAL_GPIO_PIN] == ((HHAL_GPIO_Prop*)_self_prop)->getPin()))
		{
			char* command = doc[HHAL_GPIO_COMMAND];

			if (!strcmp(command, HHAL_GPIO_READ_PROPERTIES))
			{
				GPIORead();

				res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_OK;
				res_doc[HHAL_GPIO_PIN] = ((HHAL_GPIO_Prop*)_self_prop)->getPin();
				res_doc[HHAL_GPIO_MODE] = ((HHAL_GPIO_Prop*)_self_prop)->getMode();
				res_doc[HHAL_GPIO_STATE] = ((HHAL_GPIO_Prop*)_self_prop)->getState();

				serializeJson(res_doc, res, res_len);

				return 0;
			}
			else if(!strcmp(command, HHAL_GPIO_WRITE_PROPERTIES))
			{
				if (json_object.containsKey(HHAL_GPIO_STATE))
				{
					if (json_object.containsKey(HHAL_GPIO_MODE))
					{
						uint8_t mode = doc[HHAL_GPIO_MODE];
						if (mode != ((HHAL_GPIO_Prop*)_self_prop)->getMode())
						{
							((HHAL_GPIO_Prop*)_self_prop)->setMode(mode);
							GPIOInit();
						}
					}

					bool state = doc[HHAL_GPIO_STATE];
					((HHAL_GPIO_Prop*)_self_prop)->setState(state);

					if (((HHAL_GPIO_Prop*)_self_prop)->getMode() == HHAL_GPIO_OUTPUT_MODE)
					{
						GPIOWrite();
					}

					GPIORead();

					res_doc[HHAL_RESPONSE] = HHAL_RESPONSE_OK;
					res_doc[HHAL_GPIO_PIN] = ((HHAL_GPIO_Prop*)_self_prop)->getPin();
					res_doc[HHAL_GPIO_MODE] = ((HHAL_GPIO_Prop*)_self_prop)->getMode();
					res_doc[HHAL_GPIO_STATE] = ((HHAL_GPIO_Prop*)_self_prop)->getState();

					serializeJson(res_doc, res, res_len);
					
					return 0;
				}
				else
				{
					res_doc[HHAL_RESPONSE] = HHAL_GPIO_RESPONSE_NO_VALUE_TO_WRITE;
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

int8_t HHAL_GPIO::GPIOInit()
{
	uint8_t pin = ((HHAL_GPIO_Prop*)_self_prop)->getPin();
	uint8_t mode = ((HHAL_GPIO_Prop*)_self_prop)->getMode();
	bool state = ((HHAL_GPIO_Prop*)_self_prop)->getState();

	// Hardware dependence--------------------------------------
	pinMode(pin, mode);

	if (mode == OUTPUT)
	{
		digitalWrite(pin, state);
	}
	// Hardware dependence--------------------------------------

	return 0;
}

int8_t HHAL_GPIO::GPIODeinit()
{
	uint8_t pin = ((HHAL_GPIO_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	pinMode(pin, INPUT);
	// Hardware dependence--------------------------------------

	return 0;
}

bool HHAL_GPIO::GPIORead()
{
	uint8_t pin = ((HHAL_GPIO_Prop*)_self_prop)->getPin();

	// Hardware dependence--------------------------------------
	bool state = digitalRead(pin);
	// Hardware dependence--------------------------------------

	((HHAL_GPIO_Prop*)_self_prop)->setState(state);

	return 0;
}

int8_t HHAL_GPIO::GPIOWrite()
{
	uint8_t pin = ((HHAL_GPIO_Prop*)_self_prop)->getPin();
	bool state = ((HHAL_GPIO_Prop*)_self_prop)->getState();

	// Hardware dependence--------------------------------------
	digitalWrite(pin, state);
	// Hardware dependence--------------------------------------

	return 0;
}
 

// setter -----------------------------------------------------------------------------------------------
int8_t HHAL_GPIO::setProp(HHAL_Prop* prop)
{
	*((HHAL_GPIO_Prop*)_self_prop) = *((HHAL_GPIO_Prop*)prop);

	return 0;
}
// setter -----------------------------------------------------------------------------------------------


// getter -----------------------------------------------------------------------------------------------
HHAL_Prop* HHAL_GPIO::getProp()
{
	return _self_prop;
}
// getter -----------------------------------------------------------------------------------------------

#endif