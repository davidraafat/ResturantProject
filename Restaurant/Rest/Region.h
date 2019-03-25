#pragma once
#include "Order.h"
#include "Motorcycle.h"
#include "..\Generic_DS\List.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\ProQueue.h"

class Region
{
	List<Order*> normalOrders;                               //the list of normal orders
	Queue<Order*> frozenOrders;                              //the list of the frozen orders
	ProQueue<Order*> vipOrders;                              //the list of vip orders 
	Queue<Motorcycle> frozenMotors;                          //the list of frozen motorcycles
	Queue<Motorcycle> fastMotors;                            //the list of fast motorcycles
	Queue<Motorcycle> normalMotors;                          //the list of normal motorcycles
	int numOfFastMoto,numOfNormMoto,numOfFrozenMoto;         //the number of the Fast,Normal&Frozen motorcycles
	int numOfVipOrder,numOfNormOrders,numOfFrozenOrders;     //the number of the VIP,Normal&Frozen Orders
	Queue<Order*> deliveriedOrder;                           //the list of deliveried orders
	int numOfDeliveriedOrders;                               //the number of deliveried orders in this region
	int totalWait,totalServes;                               //total time wait & service to calculate avg
    REGION regionType;                                       //the type of region A,B,C or D
public:
	bool cancelOrder(Order *& deletedOrders);                 //interface between Restaurant & region to cancel Normal order
	bool assignNormal();                                     //interface between Resturant & region to assign Normal order
	bool assignVIP ();                                       //interface between Restaurant & region to assign VIP order
	bool assignFrozen();                                     //interface between Restaurant & region to assign  frozen order
	Region(REGION);
	Region();                                                //Default Constractor
	~Region();
	void addNormalOrder(Order*);                             //Add Normal order to the normal orders list
	REGION GetRegion();                                      //Get the type of this Region
	void addFrozenOrder(Order*);                             //Add Frozen order to the frozen orders list
	void addVipOrder(Order*);                                //Add VIP order to the Vip orders list
	int getNFastMotors();                                    //Get the # of Fast Motors
	int getNNormMotors();                                    //Get the # of Normal Motors
	int getNFrozenMotors();                                  //Get the # of Frozen Motors
	int getNNOrders();                                       //Get the # of Normal Orders
	int getNFOrders();                                       //Get the # of Frozen Orders
	int getNVipOrder();                                      //Get the # of VIP Orders
	void setRegion(REGION);
	void setmotorsinfo(int sn, int sf, int sv, int nn, int nf, int nv);
};

