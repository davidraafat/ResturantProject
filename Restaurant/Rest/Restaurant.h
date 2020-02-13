#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\ProQueue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\PromotionEvent.h"
#include "..\Events\CancellationEvent.h"
#include "Region.h"
#include "Order.h"
#include <fstream>


// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	// TODO: Add More Data Members As Needed
	//
	List<Order*> MainOrders;
	int numOfOrders;
	int speedOfFastMoto, speedOfNormMoto, speedOfFrozenMoto;         //the number of the Fast,Normal&Frozen motorcycles
	Region *  regionA, *regionB, *regionC, *regionD;                 //the 4 region for each resturant
	int TimeOrdProm;
	bool notdele, notpromot;
public:
	
	Restaurant();
	~Restaurant();

	void Read();
	GUI*getpGUI();
	void RunSimulation();

	void AddEvent(Event* pE);	                          //adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	                  //executes all events at current timestep

	void stepByStepMode();                                //Step by step mode 

	Order* FindOrder(int ID);

	void cancellNormal(int ID,int time);
	void PromoteOrder(int ID,double extraMoney,int);
	///
	
	void PrepareDrawingOrders();
	void PrintInfoSB(int time,bool=0,bool=0);
	/// 
	Region *getRegion(REGION R);                           //return region 

	void setTimeOrdPr(int);
	int getTimeOrdPr();

	void setNormalorder(Order*);
	void setviporder(Order*);
	void setfrozenorder(Order*);

	void assignall();                                       //Function for phase 1 only to cancell 1 form each type of order    

    ORD_TYPE ChangeTypeOrd(char n);                         // change the order type 
	REGION ChangeTypeReg(char n);                           //change the region type 

	void invalid();
};

#endif
