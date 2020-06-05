#ifndef __HHAL__
#define __HHAL__

#include "Arduino.h"
#include "HHAL_Prop.h"
#include <ArduinoJson.h>

#define MAX_JSON_DOC_SIZE 200

#define HHAL_RESPONSE "RESPONSE"
#define HHAL_RESPONSE_OK "OK"
#define HHAL_RESPONSE_NO_COMMAND "NO COMMAND"
#define HHAL_RESPONSE_INVAILED_COMMAND "INVAILED COMMAND"


class HHAL
{
protected:
	HHAL_Prop *_self_prop;

public:
	HHAL();

	virtual int8_t begin();
	virtual int8_t end();
	virtual int8_t messageHandler(char* mess, uint32_t mess_len, char* res, uint32_t res_len);

	// setter -----------------------------
	virtual int8_t setProp(HHAL_Prop*);
	// setter -----------------------------

	//getter-------------------------------
	virtual HHAL_Prop* getProp();
	//getter-------------------------------
};

HHAL::HHAL()
{

}


#endif