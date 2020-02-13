#include "Region.h"



Region::Region()
{
}
///////////////////////////////
Region::Region(REGION type)
{
	regionType=type;
	numOfFastMoto = 0; 
	numOfNormMoto = 0;
	numOfFrozenMoto = 0;
	numOfVipOrder = 0; 
	numOfNormOrders = 0;
	numOfFrozenOrders = 0;
	numOfDeliveriedOrders = 0;
	totalWait=0;
	totalServes=0;
}
///////////////////////////////

	Region::~Region()
{
  normalOrders.clear(); //the list of normal orders
  Motorcycle*temp;
  
  while (!fastMotors.isEmpty())
  {
	  fastMotors.dequeue(temp);
	  delete temp;
  }
  while (!frozenMotors.isEmpty())
  {
	  frozenMotors.dequeue(temp);
	  delete temp;
  }

  while (!normalMotors.isEmpty())
  {
	  normalMotors.dequeue(temp);
	  delete temp;
  }
}
//////////////////////////////////////////
//Functions in region class implementation:
//1-Add Normal Orders to the normal orders list
void Region::addNormalOrder(Order* newOrder)
{
	if(newOrder->GetType()==TYPE_NRM && newOrder->GetRegion()==GetRegion())
	{
		
		normalOrders.insert(newOrder);
		numOfNormOrders++;
	}
}
//////////////////////////////////////////
//2-Add the Vip Order
void Region::addVipOrder(Order *newVipOrder)
{
	if(newVipOrder->GetType()==TYPE_VIP && newVipOrder->GetRegion()==GetRegion())
	{
		vipOrders.enqueue(newVipOrder,newVipOrder->getPriority());
		numOfVipOrder++;
	}
}
////////////////////////////////////////////
//3-Add the Frozen Order 
void Region::addFrozenOrder(Order* newFrozenOrder)
{
		if(newFrozenOrder->GetType()==TYPE_FROZ && newFrozenOrder->GetRegion()==GetRegion())
			{
				bool check=frozenOrders.enqueue(newFrozenOrder);
				if(check)
					numOfFrozenOrders++;
			}
}

/////////////////////////////////////////
//4-Assign Normal Orders
Order* Region::assignNormal()
{
	Order * temp;
	if(normalOrders.removehead(temp))
	numOfNormOrders--;
	//deliveriedOrder.enqueue(temp);         //@ phase2
	return temp;
}
/////////////////////////////////////////
//5-Assign VIP Orders
Order* Region::assignVIP()
{
	Order * temp;
	if(vipOrders.dequeue(temp))
	numOfVipOrder--;
	//deliveriedOrder.enqueue(temp);         //@ phase2
	return temp;
}


/////////////////////////////////////////
//6-Assign Frozen Orders
Order* Region::assignFrozen()
{
	Order * temp;
	if(frozenOrders.dequeue(temp))
	numOfFrozenOrders--;
	//deliveriedOrder.enqueue(temp);            //@ phase2
	return temp;
}

////////////////////////////////////////
//7-Cancel a Normal Order on the list
bool Region::cancelOrder(Order* &canOrder)
{
	bool check=normalOrders.remove(canOrder);
	if (check)
	numOfNormOrders--;

	return check;
}

///////////////////////////////////////////
//9-get num of fast moto
int Region::getNFastMotors()
{
	return numOfFastMoto;
}

///////////////////////////////////////////
//10-get num of normal moto
int Region::getNNormMotors()
{
	return numOfNormMoto;
}
///////////////////////////////////////////
//11-get num of frozin moto
int Region::getNFrozenMotors()
{
	return numOfFrozenMoto;
}
///////////////////////////////////////////
//12-get num of Normal orders
int Region::getNNOrders()
{
	return numOfNormOrders;
}
///////////////////////////////////////////
//13-get num of frozen orders
int Region::getNFOrders()
{
	return numOfFrozenOrders;
}
///////////////////////////////////////////
//14-get num of Vip orders
int Region::getNVipOrder()
{
	return numOfVipOrder;
}

///////////////////////////////////////////
//15-Set Region to instance
void Region::setRegion(REGION r)
{
regionType=r;
}


/////////////////////////////////////////////
//16-Get the region type
REGION Region::GetRegion()
{
	return regionType;
}

////////////////////////
//17-Set Motors info
void Region::setmotorsinfo(int sn, int sf, int sv, int nn, int nf, int nv)
{
	Motorcycle* Newm;
	for (int i = 0; i < nn; i++)
	{
		Newm = new Motorcycle(i+1, TYPE_NRM,sn, regionType, IDLE);
		normalMotors.enqueue(Newm,Newm->getreturnedTime()*-1);
		numOfNormMoto++;
	}


	for (int i = 0; i < nf; i++)
	{
		Newm = new Motorcycle(i + 1, TYPE_FROZ, sf, regionType, IDLE);
		frozenMotors.enqueue(Newm,Newm->getreturnedTime()*-1);
		numOfFrozenMoto++;
	}
	

	for (int i = 0; i < nv; i++)
	{
		Newm = new Motorcycle(i + 1, TYPE_VIP, sv, regionType, IDLE);
		fastMotors.enqueue(Newm,Newm->getreturnedTime()*-1);
		numOfFastMoto++;
	}
	
}

/////////////////////////////////
Order*const*Region::NormalToArr()
{
	
	return normalOrders.toArray();
}
 ///////////////////////////
 Order*const*Region::FrozenToArr()
 {
 
	 return frozenOrders.toArray();
 }

 ////////////////////////
 Order*const*Region::VIPToArr()
 {
	 return vipOrders.toArray();
 }