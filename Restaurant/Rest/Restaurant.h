#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\ProQueue.h"
#include "Region.h"
#include "Order.h"
#include <fstream>
#include "..\Events\ArrivalEvent.h"
#include "..\Events\PromotionEvent.h"
#include "..\Events\CancellationEvent.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	List<Order*> MainOrders;
	int numOfOrders;
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important:This is just for demo
	// TODO: Add More Data Members As Needed
	//
	int speedOfFastMoto, speedOfNormMoto, speedOfFrozenMoto;         //the number of the Fast,Normal&Frozen motorcycles
	Region *  regionA, *regionB, *regionC, *regionD;   //the 4 region for each resturant
	int TimeOrdProm;
public:
	
	Restaurant();
	~Restaurant();
	GUI*getpGUI();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	Order* FindOrder(int ID);
	void cancellNormal(int ID);
	void PromoteOrder(int ID,double extraMoney);
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 
	void stepByStepMode();          //Step by step mode 
	Region *getRegion(REGION R);    //return region 
	void setTimeOrdPr(int);
	int getTimeOrdPr();
	void setNormalorder(Order*);
	void setviporder(Order*);
	void setfrozenorder(Order*);
	void assignall();                //Function for phase 1 only to cancell 1 form each type of order    
	////////////
   ORD_TYPE ChangeTypeOrd(char n); // change the order type 
	REGION ChangeTypeReg(char n); //change the region type 
	void Read();


};

#endif
