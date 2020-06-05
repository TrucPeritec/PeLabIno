#ifndef __HHAL_PROP__
#define __HHAL_PROP__

#include "Arduino.h"

class HHAL_Prop
{
protected:
	bool _occupied;

public:
	HHAL_Prop();
	bool isOccupied();
	int8_t updateOccupied(bool occupied);
};


HHAL_Prop::HHAL_Prop()
{
	_occupied = false;
}


bool HHAL_Prop::isOccupied()
{
	return _occupied;
}


int8_t HHAL_Prop::updateOccupied(bool occupied)
{
	_occupied = occupied;
}



#endif