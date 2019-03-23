#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	regionA  =new Region(A_REG);
	regionB  =new Region(B_REG);
	regionC  =new Region(C_REG);
	regionD  =new Region(D_REG);

		pGUI=new GUI;
}

void Restaurant::RunSimulation()
{
	if(pGUI ==NULL)

	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


///////////////////////////
Order* Restaurant::FindOrder(int ID)
{
	
	Order*tm=NULL;
	Node<Order*>* j=MainOrders.getHead();
	while(j)
	{
		if(j->getItem()->GetID()==ID)
	{
	tm= j->getItem();
	break;
	}
	else j=(j->getNext());
	}
		
	return tm;
}

////////////////////////
void Restaurant::cancellNormal(int ID)
{
	Order* deletedOrder=FindOrder(ID);
	REGION temp=deletedOrder->GetRegion();
	switch(temp)
	{
	
		case A_REG:
		regionA->cancelOrder(deletedOrder);
		MainOrders.remove(deletedOrder);
	    break;
	
		case B_REG:
		regionB->cancelOrder(deletedOrder);
		MainOrders.remove(deletedOrder);
	    break;

		case C_REG:
		regionC->cancelOrder(deletedOrder);
		MainOrders.remove(deletedOrder);
	    break;

		case D_REG:
		regionD->cancelOrder(deletedOrder);
		MainOrders.remove(deletedOrder);
	    break;
	
	
	}

}
//////////////////////////
void Restaurant::PromoteOrder(int ID,double extraMoney)
{
	Order * promoted=FindOrder(ID);
	REGION temp=promoted->GetRegion();
	switch(temp)
	{
	//Need to add converter from Normal to VIP
		case A_REG:

		regionA->cancelOrder(promoted);
		promoted->setExtraMoney(extraMoney);
	    break;
	
		case B_REG:
		regionB->cancelOrder(promoted);
		promoted->setExtraMoney(extraMoney);

	    break;

		case C_REG:
		regionC->cancelOrder(promoted);
		promoted->setExtraMoney(extraMoney);

	    break;

		case D_REG:
		regionD->cancelOrder(promoted);
		promoted->setExtraMoney(extraMoney);

	    break;
	
	
	}
}
//////////////////////////
Restaurant::~Restaurant()
{
		delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		//pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		//AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
	MainOrders.insert(pOrd);
	
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}
GUI* Restaurant::getpGUI(){return pGUI;}
Region* Restaurant::getRegion(REGION R)
{
	switch (R)
	{
	case A_REG:return this->regionA;
	case B_REG:return this->regionB;
	case C_REG:return this->regionC;
	case D_REG:return this->regionD;
	
	}	
	
	}

	void Restaurant::setTimeOrdPr(int n )
	{
	TimeOrdProm=(n>0)?n:0;
	}

	int Restaurant::getTimeOrdPr()
	{return TimeOrdProm;}

/// ==> end of DEMO-related function