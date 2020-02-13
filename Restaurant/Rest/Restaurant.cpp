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
	notdele = 0;
	notpromot = 0;
	pGUI = new GUI;

}

//////////////////////////
Restaurant::~Restaurant()
{
	    delete regionA;
	    delete regionB;
	    delete regionC;
	    delete regionD;
	Order *delOrd;
	while (MainOrders.removehead(delOrd))
	{
		delete delOrd;
	}
	Event*temp;
	while(!EventsQueue.isEmpty())
	{
		EventsQueue.dequeue(temp);
		delete temp;
	}
	
		delete pGUI;

}

/////////////////////////
void Restaurant ::Read(){
	ArrivalEvent* ev;
	CancellationEvent* ec;
	PromotionEvent* ep;
	ORD_TYPE ord;
	REGION reg;
	int time, id, dest, mon, extrMon;
	int sn, sf, sv, n, f, v, timeProm, numEvent;
	char typeEve, typeorder, typeReg;
	pGUI->PrintMessage("enter file name please ",1);
	string s = pGUI->GetString();
	ifstream myfile(s + ".txt");
	
	if (myfile.is_open())
	{
		myfile >> sn >> sf >> sv;
		myfile >> n >> f >> v;
		if ((sn > 0) && (sf > 0) && (sv > 0) && (n > 0) && (f > 0) && (v > 0))
		{
			getRegion(A_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

			myfile >> n >> f >> v;
			if ( (n > 0) && (f > 0) && (v > 0))
			{
				getRegion(B_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

				myfile >> n >> f >> v;
				if ( (n > 0) && (f > 0) && (v > 0))
				{
					getRegion(C_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

					myfile >> n >> f >> v;
					if ( (n > 0) && (f > 0) && (v > 0))
					{
						getRegion(D_REG)->setmotorsinfo(sn, sf, sv, n, f, v);

						myfile >> timeProm >> numEvent;////////
						setTimeOrdPr(timeProm);
						for (int i = 0; i < numEvent; i++)//
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
					else
						pGUI->PrintMessage("your orders cannot be saved ; becouse you enter invalid data at first", 1);
				}
				else
					pGUI->PrintMessage("your orders cannot be saved ; becouse you enter invalid data at first", 1);
			}
			else
				pGUI->PrintMessage("your orders cannot be saved ; becouse you enter invalid data at first", 1);
			}
		else
			pGUI->PrintMessage("your orders cannot be saved ; becouse you enter invalid data at first", 1);
	}
	else {
		pGUI->PrintMessage("File cannot be opened",1);
	}
}
//////////////////////////
GUI* Restaurant::getpGUI() 
{
	return pGUI;
}

//////////////////////////
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
	};

}

//////////////////////////////////  Event handling functions   /////////////////////////////
//adds a new event to the queue of events
void Restaurant::AddEvent(Event* pE)	
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
		delete pE;	            	//deallocate event object from memory
	}

}

///////////////////////////
void Restaurant :: stepByStepMode(){	
		
	pGUI->PrintMessage("Step by step mode. ",1);
	pGUI->UpdateInterface();

	int EvTime = 0;
	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the ToDrawOrders
		//Let's draw all arrived orders by passing them to the GUI to draw

		PrepareDrawingOrders();	
		PrintInfoSB(CurrentTimeStep,notdele,notpromot);
		//wiat for mouse click
	    pGUI->waitForClick();
	    assignall();
		PrintInfoSB(CurrentTimeStep,notdele,notpromot);
		pGUI->UpdateInterface();
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep.
		pGUI->ResetDrawingList();

	}
	
}
/////////////////////////
Order*  Restaurant::FindOrder(int ID)
{
	Node<Order*>*ptr;
	for (int i = 1; i <= numOfOrders; i++)
	{
		ptr=MainOrders.getNodeAt(i);
		if(ptr->getItem()->GetID()==ID)
			return ptr->getItem();
		ptr=ptr->getNext();
	}
	return NULL;
}

//////////////////////////
void Restaurant::cancellNormal(int ID,int time)
{

	Order* deletedOrder=FindOrder(ID);
	if (deletedOrder)
	{ 
		if (deletedOrder->GetType() == TYPE_NRM)
		{
			REGION temp = deletedOrder->GetRegion();
			switch (temp)
			{

			case A_REG:
				regionA->cancelOrder(deletedOrder);
				if (MainOrders.remove(deletedOrder))
				{
					numOfOrders--;
				}
				break;

			case B_REG:
				regionB->cancelOrder(deletedOrder);
				if (MainOrders.remove(deletedOrder))
				{
					numOfOrders--;
				}
				break;

			case C_REG:
				regionC->cancelOrder(deletedOrder);
				if (MainOrders.remove(deletedOrder))
				{
					numOfOrders--;
				}
				break;

			case D_REG:
				regionD->cancelOrder(deletedOrder);
				if (MainOrders.remove(deletedOrder))
				{
					numOfOrders--;
				}
				break;


			}
			PrepareDrawingOrders();
		}
		else 
		{
			
			notdele =1;
		}

	}
	else notdele =1;
}

//////////////////////////
void Restaurant::PromoteOrder(int ID,double extraMoney, int time)
{
	Order * promoted=FindOrder(ID);
	if (promoted)
	{
		if (promoted->GetType() == TYPE_NRM)
		{
			REGION temp = promoted->GetRegion();
			switch (temp)
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
			}
			PrepareDrawingOrders();
			PrintInfoSB(time);
		}
		else
			notpromot = 1;
		
	}
	else notpromot = 1;
}

///////////////////////////
void Restaurant::PrepareDrawingOrders()
{
	pGUI->ResetDrawingList();
 Order*const*temp=regionA->VIPToArr();
		for(int i=0;i<regionA->getNVipOrder();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;
		temp=regionA->FrozenToArr();
		for(int i=0;i<regionA->getNFOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionA->NormalToArr();
		for(int i=0;i<regionA->getNNOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		//////////////////
			temp=regionB->VIPToArr();
		for(int i=0;i<regionB->getNVipOrder();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionB->FrozenToArr();
		for(int i=0;i<regionB->getNFOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionB->NormalToArr();
		for(int i=0;i<regionB->getNNOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		/////////////////////
			temp=regionC->VIPToArr();
		for(int i=0;i<regionC->getNVipOrder();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionC->FrozenToArr();
		for(int i=0;i<regionC->getNFOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionC->NormalToArr();
		for(int i=0;i<regionC->getNNOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		//////////////////
	    temp=regionD->VIPToArr();
		for(int i=0;i<regionD->getNVipOrder();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionD->FrozenToArr();
		for(int i=0;i<regionD->getNFOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();

	     }
		delete [] temp;

		temp=regionD->NormalToArr();
		for(int i=0;i<regionD->getNNOrders();i++)
	     { 
			pGUI->AddOrderForDrawing(temp[i]);
			pGUI->UpdateInterface();
	     }
		delete [] temp;


}
////////////////////////////
void Restaurant::PrintInfoSB(int time,bool nc,bool np)
{
	pGUI->PrintMessage(std::to_string(time),1);
	    pGUI->PrintMessage("Region A: NormalO= "+std::to_string(regionA->getNNOrders())+" ,VIPO="+std::to_string(regionA->getNVipOrder())+" ,FrozenO="+std::to_string(regionA->getNFOrders())+"  - NormalMotors="+std::to_string(regionA->getNNormMotors())+" ,FastMotors="+std::to_string(regionA->getNFastMotors())+" ,FrozenMotors="+std::to_string(regionA->getNFrozenMotors()),0,1);
		pGUI->PrintMessage("Region B: NormalO= "+std::to_string(regionB->getNNOrders())+" ,VIPO="+std::to_string(regionB->getNVipOrder())+" ,FrozenO="+std::to_string(regionB->getNFOrders())+"  - NormalMotors="+std::to_string(regionB->getNNormMotors())+" ,FastMotors="+std::to_string(regionB->getNFastMotors())+" ,FrozenMotors="+std::to_string(regionB->getNFrozenMotors()),0,2);
		pGUI->PrintMessage("Region C: NormalO= "+std::to_string(regionC->getNNOrders())+" ,VIPO="+std::to_string(regionC->getNVipOrder())+" ,FrozenO="+std::to_string(regionC->getNFOrders())+"  - NormalMotors="+std::to_string(regionC->getNNormMotors())+" ,FastMotors="+std::to_string(regionC->getNFastMotors())+" ,FrozenMotors="+std::to_string(regionC->getNFrozenMotors()),0,3);
		pGUI->PrintMessage("Region D: NormalO= "+std::to_string(regionD->getNNOrders())+" ,VIPO="+std::to_string(regionD->getNVipOrder())+" ,FrozenO="+std::to_string(regionD->getNFOrders())+"  - NormalMotors="+std::to_string(regionD->getNNormMotors())+" ,FastMotors="+std::to_string(regionD->getNFastMotors())+" ,FrozenMotors="+std::to_string(regionD->getNFrozenMotors()),0,4);
		if (nc&&np)
		{
			pGUI->PrintMessage("This ordered can't be cancelled!", 0, 5);
			notdele = 0;

			pGUI->PrintMessage("This ordered can't be promoted!", 0,6);
			notpromot = 0;

		}
       else if (nc)
		{
			pGUI->PrintMessage("This ordered can't be cancelled!", 0, 5);
			notdele = 0;
		}
		else if (np)
		{
			pGUI->PrintMessage("This ordered can't be promoted!", 0, 5);
			notpromot = 0;

		}
}

/////////////////////////////
Region* Restaurant::getRegion(REGION R)
{
	switch (R)
	{
	case A_REG:return this->regionA;
	case B_REG:return this->regionB;
	case C_REG:return this->regionC;
	case D_REG:return this->regionD;
	//this case is impossible but to avoid warnings
	default:return this->regionA;
	}

}

////////////////////////////
void Restaurant::setTimeOrdPr(int n)
{
	TimeOrdProm = (n>0) ? n : 0;
}

////////////////////////////
int Restaurant::getTimeOrdPr()
{
	return TimeOrdProm;
}

///////////////////////////// 
void Restaurant::setNormalorder(Order* Inorder)
{
	MainOrders.insert(Inorder);
	numOfOrders++;
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

//////////////////////////////
void Restaurant::setfrozenorder(Order* Inorder)
{
	MainOrders.insert(Inorder);
	numOfOrders++;
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

///////////////////////////////
void Restaurant::setviporder(Order *Inorder)
{
	MainOrders.insert(Inorder);
	numOfOrders++;
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

//////////////////////////
void Restaurant::assignall()
{
	Order*deleted;
	//Region A
	deleted=regionA->assignNormal();
   if(	MainOrders.remove(deleted))
	   numOfOrders--;
	
	deleted=regionA->assignFrozen();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionA->assignVIP();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	/////////Region B
	deleted=regionB->assignNormal();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionB->assignFrozen();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionB->assignVIP();
    if(	MainOrders.remove(deleted))
	   numOfOrders--;

	///////////Region C
	deleted=regionC->assignNormal();
  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionC->assignFrozen();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionC->assignVIP();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	/////////Region D
	deleted=regionD->assignNormal();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;

	deleted=regionD->assignFrozen();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;
	
	deleted=regionD->assignVIP();
	  if(	MainOrders.remove(deleted))
	   numOfOrders--;
		
	PrepareDrawingOrders();
}

////////////////////////////////////
ORD_TYPE Restaurant::ChangeTypeOrd(char n){
	if (n == 'N')      { return TYPE_NRM; }
	else if (n == 'V') { return TYPE_VIP; }
	else   { return TYPE_FROZ; }
}

////////////////////////////
REGION Restaurant:: ChangeTypeReg(char n){
	if      (n == 'A') { return A_REG; }
	else if (n == 'B') { return B_REG; }
	else if (n == 'C') { return C_REG; }
	else   { return D_REG; }
	
}

////////////////////////////
void Restaurant::invalid()
{
	pGUI->PrintMessage("you Enter invalid data this order can not save!. ", 0, 5);
} 