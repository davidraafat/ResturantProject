#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Restaurant.h"
using namespace std;

Restaurant::Restaurant() 
{
	regionA = new Region(A_REG);
	regionB = new Region(B_REG);
	regionC = new Region(C_REG);
	regionD = new Region(D_REG);
	numOfOrders = 0;
	pGUI = new GUI;
}

void Restaurant::RunSimulation()
{
	if (pGUI == NULL)
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		stepByStepMode();
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
Order*  Restaurant::FindOrder(int ID)
{
	
	Node<Order*>*ptr1 = MainOrders.getHead();
	for (int i = 0; i < numOfOrders; i++)
	{
		if (ptr1 == NULL) return nullptr;
		else if (ptr1->getItem()->GetID() == ID)
			return (ptr1->getItem());
		else
			{

				ptr1=ptr1->getNext();
		   }
	}
	return NULL;
}

//////////////////////////
void Restaurant::cancellNormal(int ID)
{

	Order* deletedOrder=FindOrder(ID);
	if (deletedOrder->GetType()==TYPE_NRM)
	{
	REGION temp=deletedOrder->GetRegion();
	switch(temp)
	{
	
		case A_REG:
		regionA->cancelOrder(deletedOrder);
		if (MainOrders.remove(deletedOrder))
			{delete deletedOrder;
		numOfOrders--;}
	    break;
	
		case B_REG:
		regionB->cancelOrder(deletedOrder);
			if (MainOrders.remove(deletedOrder))
			{delete deletedOrder;
		numOfOrders--;}
	    break;

		case C_REG:
		regionC->cancelOrder(deletedOrder);
		if (MainOrders.remove(deletedOrder))
			{delete deletedOrder;
		numOfOrders--;}
	    break;

		case D_REG:
		regionD->cancelOrder(deletedOrder);
			if (MainOrders.remove(deletedOrder))
			{
				delete deletedOrder;
		        numOfOrders--;}
	    break;
	
	
	}
	}
	else return;
}
//////////////////////////
void Restaurant::PromoteOrder(int ID,double extraMoney)
{
	Order * promoted=FindOrder(ID);
	if (promoted->GetType()==TYPE_NRM)
	{
	REGION temp=promoted->GetRegion();
	switch(temp)
	{
	//Need to add converter from Normal to VIP
		case A_REG:

		regionA->cancelOrder(promoted);
		promoted->setType(TYPE_VIP);
		promoted->setExtraMoney(extraMoney);
		regionA->addVipOrder(promoted);
	    break;
	
		case B_REG:
		regionB->cancelOrder(promoted);
		promoted->setType(TYPE_VIP);
		promoted->setExtraMoney(extraMoney);
		regionB->addVipOrder(promoted);


	    break;

		case C_REG:
		regionC->cancelOrder(promoted);
		promoted->setType(TYPE_VIP);
		promoted->setExtraMoney(extraMoney);
		regionC->addVipOrder(promoted);

	    break;

		case D_REG:

		regionD->cancelOrder(promoted);
		promoted->setType(TYPE_VIP);
		promoted->setExtraMoney(extraMoney);
		regionD->addVipOrder(promoted);


	    break;
	
	
	}}
	else return;
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
	//for(int i=0; i<EventCnt; i++)
	//{
	//	int O_id = i+1;
	//	
	//	//Rendomize order type
	//	int OType;
	//	if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
	//		OType = TYPE_VIP;
	//	else if(i<EventCnt*0.5)	
	//		OType = TYPE_FROZ;	//let next 30% be Frozen
	//	else
	//		OType = TYPE_NRM;	//let the rest be normal

	//	
	//	int reg = rand()% REG_CNT;	//randomize region


	//	//Randomize event time
	//	EvTime += rand()%4;
	////	pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
	//	//AddEvent(pEv);

	//}	

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
	numOfOrders++;
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


GUI* Restaurant::getpGUI() 
{
	return pGUI;
}


Region* Restaurant::getRegion(REGION R)
{
	switch (R)
	{
	case A_REG:return this->regionA;
	case B_REG:return this->regionB;
	case C_REG:return this->regionC;
	case D_REG:return this->regionD;
		//this case is impossible
	default:return this->regionA;
	}

}

void Restaurant::setTimeOrdPr(int n)
{
	TimeOrdProm = (n>0) ? n : 0;
}

int Restaurant::getTimeOrdPr()
{
	return TimeOrdProm;
}

void Restaurant::setNormalorder(Order* Inorder)
{
	REGION type = Inorder->GetRegion();
	switch (type)
	{
	case (A_REG):
		regionA->addNormalOrder(Inorder);
		break;

	case (B_REG):
		regionB->addNormalOrder(Inorder);
		break;
	case (D_REG):
		regionD->addNormalOrder(Inorder);
		break;
	case (C_REG):
		regionC->addNormalOrder(Inorder);
		break;

	}
}



void Restaurant::setfrozenorder(Order* Inorder)
{
	REGION type = Inorder->GetRegion();
	switch (type)
	{
	case (A_REG):
		regionA->addFrozenOrder(Inorder);
		break;

	case (B_REG):
		regionB->addFrozenOrder(Inorder);
		break;
	case (D_REG):
		regionD->addFrozenOrder(Inorder);
		break;
	case (C_REG):
		regionC->addFrozenOrder(Inorder);
		break;

	}
}

void Restaurant::setviporder(Order *Inorder)
{
	REGION type = Inorder->GetRegion();
	switch (type)
	{
	case (A_REG):
		regionA->addVipOrder(Inorder);
		break;

	case (B_REG):
		regionB->addVipOrder(Inorder);
		break;
	case (D_REG):
		regionD->addVipOrder(Inorder);
		break;
	case (C_REG):
		regionC->addVipOrder(Inorder);
		break;

	}
}

void Restaurant :: stepByStepMode(){	
	Order* pOrd;
	Event* pEv;
	//srand(time(NULL));
	pGUI->PrintMessage("Step by step mode. ");
	pGUI->UpdateInterface();	
	int EvTime = 0;
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
		while (regionA->getfront())
		{
		
		
		}
		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		//wiat for mouse click 
		pGUI->waitForClick();

		CurrentTimeStep++;	//advance timestep.
	    pGUI->waitForClick();
	    assignall();
	}
	
}

void Restaurant::assignall()
{
	Order*deleted;

	deleted=regionA->assignNormal();
	if(MainOrders.remove(deleted))


	delete deleted;

	deleted=regionA->assignFrozen();
		if(MainOrders.remove(deleted))

	 delete deleted;


	deleted=regionA->assignVIP();
		if(MainOrders.remove(deleted))

		 delete deleted;


	/////////
	deleted=regionB->assignNormal();
		if(MainOrders.remove(deleted))

		 delete deleted;


	deleted=regionB->assignFrozen();
		if(MainOrders.remove(deleted))

		 delete deleted;


	deleted=regionB->assignVIP();
		if(MainOrders.remove(deleted))

		 delete deleted;


	///////////
	deleted=regionC->assignNormal();
		if(MainOrders.remove(deleted))

		 delete deleted;


	deleted=regionC->assignFrozen();
		if(MainOrders.remove(deleted))

		 delete deleted;


	deleted=regionC->assignVIP();
		if(MainOrders.remove(deleted))

		 delete deleted;

	/////////
	deleted=regionD->assignNormal();
	if(MainOrders.remove(deleted))
		delete deleted;


	deleted=regionD->assignFrozen();
	if(MainOrders.remove(deleted))

	 delete deleted;


	deleted=regionD->assignVIP();
	if(MainOrders.remove(deleted))

	 delete deleted;

}


void Restaurant ::Read(){
	ArrivalEvent* ev;
	CancellationEvent* ec;
	PromotionEvent* ep;
	ORD_TYPE ord;
	REGION reg;
	int time, id, dest, mon, extrMon;
	int sn, sf, sv, n, f, v, timeProm, numEvent;
	char typeEve, typeorder, typeReg;
	getpGUI()->PrintMessage("enter file name please ");
	ifstream myfile(getpGUI()->GetString() + ".txt");

	if (myfile.is_open())
	{
		myfile >> sn >> sf >> sv;
		myfile >> n >> f >> v;
		getRegion(A_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

		myfile >> n >> f >> v;
		getRegion(B_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

		myfile >> n >> f >> v;
		getRegion(C_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

		myfile >> n >> f >> v;
		getRegion(D_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

		myfile >> timeProm >> numEvent;////////
		setTimeOrdPr(timeProm);
		for (int i = 0; i<numEvent; i++)//
		{
			myfile >> typeEve;
			if (typeEve == 'R')
			{
				myfile >> time >> typeorder >> id >> dest >> mon >> typeReg;
				ord = ChangeTypeOrd(typeorder);
				reg = ChangeTypeReg(typeReg);
				ev = new ArrivalEvent(time, ord, id, dest, mon, reg);
				AddEvent(ev);
			}
			else if (typeEve == 'X')
			{
				myfile >> time >> id;
				ec = new CancellationEvent(time, id);
				AddEvent(ec);
			}
			else if (typeEve == 'P')
			{
				myfile >> time >> id >> extrMon;
				ep = new PromotionEvent(time, id, extrMon);
				AddEvent(ep);

			}
		}
		myfile.close();
	}
	else {
		getpGUI()->PrintMessage("File cannot be opened");
	}
}

ORD_TYPE Restaurant::ChangeTypeOrd(char n){
	if (n == 'N') { return TYPE_NRM; }
	else if (n == 'V') { return TYPE_VIP; }
	else if (n=='F') { return TYPE_FROZ; }
}

REGION Restaurant:: ChangeTypeReg(char n){
	if (n == 'A') { return A_REG; }
	else if (n == 'B') { return B_REG; }
	else if (n == 'C') { return C_REG; }
	else if (n=='D') { return D_REG; }
}