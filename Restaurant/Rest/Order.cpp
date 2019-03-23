#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	priority=0.5*totalMoney+Distance+200/float(ArrTime);

}

//Order::Order()
//{}

float Order::getPriority()
{
	return priority;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}

void Order::setExtraMoney(double extra)
{
	totalMoney+=extra;
}


int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

double Order::getMoney()
{
	return totalMoney;
}

int Order::getArrTime()
{
	return ArrTime;
}

int Order::getServTime()
{
	return ServTime;
}

int Order::getFinishTime()
{
	return FinishTime;
}
bool Order::operator==(Order o)
{
	if(o.GetID()==ID){return true;}	
	else{return false;}	

}

