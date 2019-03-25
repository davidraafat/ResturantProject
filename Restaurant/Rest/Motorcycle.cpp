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

Motorcycle::~Motorcycle()
{
}
