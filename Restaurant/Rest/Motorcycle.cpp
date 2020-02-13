#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}

Motorcycle::Motorcycle(int id,ORD_TYPE Type,int Speed,REGION r,STATUS currentStatus)
{
	ID=id;
	type=Type;
	speed=Speed;
	region=r;
	status=currentStatus;
	returnedTime=0;
}

int Motorcycle::getID()
{
	return ID;
}

ORD_TYPE Motorcycle::getType()
{
	return type;      
}

int Motorcycle::getSpeed()
{
	return speed;
}

REGION Motorcycle::getRegion()
{
	return region; 
}

STATUS Motorcycle::getStatus()
{
	return status;
}

void Motorcycle::setStatus(STATUS s)
{
	status=s;
}

void Motorcycle::setreturnedTime(int currentTimeStep,int distance)
{
	returnedTime=currentTimeStep+(2*distance)/speed;
}

int Motorcycle::getreturnedTime()
{
	return returnedTime;
}

bool Motorcycle::compare(int TimeStep)
{
	if(returnedTime==TimeStep)
	{
		setStatus(IDLE);
	    return true;
	}
	return false;
}

Motorcycle::~Motorcycle()
{

}

