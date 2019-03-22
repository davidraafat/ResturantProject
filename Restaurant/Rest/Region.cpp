#include "Region.h"


Region::Region(REGION type)
{
	regionType=type;
	numOfFastMoto,numOfNormMoto,numOfFrozenMoto,numOfVipOrder,numOfNormOrders,numOfFrozenOrders,numOfDeliveriedOrders=0;
	totalWait=0;
	totalServes=0;
}
Region::Region(){}


Region::~Region()
{
}
 
//////////////////////////////////////////
//Functions in region class implementation:
//1-Add Normal Orders to the normal orders list
void Region::addNormalOrder(Order* newOrder){
	if(newOrder->GetType()==TYPE_NRM && newOrder->GetRegion()==GetRegion())
	{
		Node<Order*>* newOrd= new Node<Order*>;
		newOrd->setItem(newOrder);
		normalOrders.insert(newOrd);
		numOfNormOrders++;
	}
}
/////////////////////////////////////////////
//2-Get the region type
REGION Region::GetRegion(){return regionType;}
////////////////////////////////////////////
//3-Add the Frozen Order 
void Region::addFrozenOrder(Order* newFrozenOrder){
	if(newFrozenOrder->GetType()==TYPE_FROZ && newFrozenOrder->GetRegion()==GetRegion()){
		bool check=frozenOrders.enqueue(newFrozenOrder);
		if(check)
			numOfFrozenOrders++;
	}
}
//////////////////////////////////////////
//4-Add the Vip Order
void Region::addVipOrder(Order *newVipOrder){
	if(newVipOrder->GetType()==TYPE_VIP && newVipOrder->GetRegion()==GetRegion()){
		//fun. calcu priority
		vipOrders.enqueue(newVipOrder,newVipOrder->getPriority());
		numOfVipOrder++;
	}
}
////////////////////////////////////////
//5-Cancel a Normal Order on the list
bool Region::cancelOrder(Order* canOrder){
	bool check=normalOrders.remove(canOrder);
	numOfNormOrders--;
	return check;
}
/////////////////////////////////////////
//6-Assign Normal Orders
bool Region::assignNormal(){
	//Update it after time step
	Order * temp;

	bool check=normalOrders.removehead(temp);
	deliveriedOrder.enqueue(temp);
	return check;
}

/////////////////////////////////////////
//7-Assign VIP Orders
bool Region::assignVIP(){
	//Update it after time step
	Order * temp;
	bool check=vipOrders.dequeue(temp);
	deliveriedOrder.enqueue(temp);
	return check;
}

/////////////////////////////////////////
//8-Assign Frozen Orders
bool Region::assignFrozen(){
	//Update it after time step
	Order * temp;
	bool check=frozenOrders.dequeue(temp);
	deliveriedOrder.enqueue(temp);
	return check;
}
///////////////////////////////////////////
//9-get num of fast moto
int Region::getNFastMotors(){return numOfFastMoto;}
///////////////////////////////////////////
//10-get num of normal moto
int Region::getNNormMotors(){return numOfNormMoto;}
///////////////////////////////////////////
//11-get num of frozin moto
int Region::getNFrozenMotors(){return numOfFrozenMoto;}
///////////////////////////////////////////
//12-get num of Normal orders
int Region::getNNOrders(){return numOfNormOrders;}
///////////////////////////////////////////
//13-get num of frozen orders
int Region::getNFOrders(){return numOfFrozenOrders;}
///////////////////////////////////////////
//14-get num of Vip orders
int Region::getNVipOrder(){return numOfVipOrder;}

