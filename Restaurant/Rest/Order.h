#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	float priority;                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times
	
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	//Order () ;
	Order(int ID, ORD_TYPE r_Type, REGION r_region);
	virtual ~Order();
	bool operator==(Order o);
	int GetID();

	int GetType() const;
	REGION GetRegion() const;
	void SetDistance(int d);
	int GetDistance() const;

	//
	// TODO: Add More Member Functions As Needed
	//

	void setExtraMoney(double );
	double getMoney();
	int getArrTime();
	int getServTime();
	int getFinishTime();
	float getPriority();



};

#endif