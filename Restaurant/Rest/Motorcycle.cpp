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
<<<<<<< HEAD
	returnedTime=0;
=======
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
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
<<<<<<< HEAD

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
=======
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5

Motorcycle::~Motorcycle()
{
}

