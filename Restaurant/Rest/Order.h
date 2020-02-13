#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;                                     //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		                        //order type: Normal, Frozen, VIP
	REGION Region;                              //Region of this order
	int Distance;     	                        //The distance (in meters) between the order location and the resturant 
	double totalMoney;                      	//Total order money
	
	
	
	//
	// TODO: Add More Data Members As Needed
	//
	double priority;                            //Priority of this order 
	int ArrTime, ServTime, FinishTime;	        //arrival, service start, and finish times           
    
public:
	Order () ;
	Order(int ID, ORD_TYPE r_Type, REGION r_region,int Distance, double totalMoney,int ArrTime);


	int GetID();
	void setType(ORD_TYPE);
	ORD_TYPE GetType() const;
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;
    virtual ~Order();  
	//
	// TODO: Add More Member Functions As Needed
	//

	void setExtraMoney(double );
	void setpriority();
	double getMoney();
	int getArrTime();
	int getServTime();
	int getFinishTime();
	double getPriority();
	bool operator==(Order compared);

};

#endif
