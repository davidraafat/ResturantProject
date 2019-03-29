#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;    	//for each order type there is a corresponding motorcycle type 
	int speed;		    //meters it can move in one clock tick (in one timestep)
	REGION	region;  	//region of the motorcycle
	STATUS	status;	    //idle or in-service
	int returnedTime;   //time to return (current time step+ 2*distance/speed)
	

public:
	Motorcycle();
	Motorcycle(int id,ORD_TYPE Type,int Speed,REGION r,STATUS currentStatus);
	int getID();
	ORD_TYPE getType();
	int getSpeed();
	REGION getRegion();
	STATUS getStatus();
<<<<<<< HEAD
	void setreturnedTime(int,int );
	int getreturnedTime();
	void setStatus(STATUS );
	bool compare(int TimeStep);
=======
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
	virtual ~Motorcycle();

};

#endif
