#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int Dis, double totalMon, int artm)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance = Dis;
	totalMoney = totalMon;
	ArrTime = artm;
	priority=0.5*totalMoney+Distance+200/double(ArrTime);

}

Order::Order()
{
}

double Order::getPriority()
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

void Order::setType(ORD_TYPE newtype)
{
	type = newtype;

}

void Order::setExtraMoney(double extra)
{
	totalMoney+=extra;
}


ORD_TYPE Order::GetType() const
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

bool Order::operator==(Order compared)
{
	if(ID==compared.GetID())  return true;
	else return false;
}
