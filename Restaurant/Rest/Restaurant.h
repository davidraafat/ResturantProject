#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "Region.h"
#include "Order.h"
<<<<<<< HEAD
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
#include <fstream>

using namespace std;

=======
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
#include <fstream>
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
<<<<<<< HEAD
	Queue<Event*> EventsQueue;	                                 //Queue of all events that will be loaded from file
	List<Order*> MainOrders;                                     //List for all the orders in the 4  regions 
	int numOfOrders;                                             //# of the orders
=======
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	List<Order*> MainOrders;
	int numOfOrders;
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	// TODO: Add More Data Members As Needed
	//
<<<<<<< HEAD
	int speedOfFastMoto, speedOfNormMoto, speedOfFrozenMoto;     //the number of the Fast,Normal&Frozen motorcycles
	Region *  regionA, *regionB, *regionC, *regionD;             //the 4 region for each resturant
	int TimeOrdProm;                                             //time to the normal order to be promoted
=======
	int speedOfFastMoto, speedOfNormMoto, speedOfFrozenMoto;         //the number of the Fast,Normal&Frozen motorcycles
	Region *  regionA, *regionB, *regionC, *regionD;   //the 4 region for each resturant
	int TimeOrdProm;
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
public:
	
	Restaurant();
	~Restaurant();
	GUI*getpGUI();
<<<<<<< HEAD
	void AddEvent(Event* pE);	                 //adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	         //executes all events at current timestep
	void RunSimulation();                        //run the gui to simulate the system
	Order* FindOrder(int ID);                    //get pointer to the order by the id of the order
	void cancellNormal(int ID);                  //cancel normal order from the list
	void PromoteOrder(int ID,double extraMoney); //promote the normal order to VIP order
=======
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	Order* FindOrder(int ID);
	void cancellNormal(int ID);
	void PromoteOrder(int ID,double extraMoney);
>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 
	void stepByStepMode();          //Step by step mode 
	Region *getRegion(REGION R);    //return region 
<<<<<<< HEAD
	void setTimeOrdPr(int);         //set the time of the order
	int getTimeOrdPr();             //get the time of the order
	void setNormalorder(Order*);    //set the normal order in the list
	void setviporder(Order*);       // set the VIP order in the priority queue
	void setfrozenorder(Order*);    //set the frozen order in the queue
	void assignall();               //Function for phase 1 only to cancell 1 form each type of order 
	ORD_TYPE ChangeTypeOrd(char n); // change the order type 
	REGION ChangeTypeReg(char n);   //change the region type 
	void Read();                    //Read the info from the txt file 
=======
	void setTimeOrdPr(int);
	int getTimeOrdPr();
	void setNormalorder(Order*);
	void setviporder(Order*);
	void setfrozenorder(Order*);
	ORD_TYPE ChangeTypeOrd(char n); // change the order type 
	REGION ChangeTypeReg(char n); //change the region type 
	void Read();
	

	//

	//
	// TODO: Add More Member Functions As Needed
	//

	//function find order by ID

>>>>>>> f5002feb07fd46685827069b18888cec51bf56e5
};

#endif
