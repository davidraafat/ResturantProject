#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"



PromotionEvent::PromotionEvent(int time,int ID, double extra):Event(time, ID)
{
	extraMoney=extra;
}

double PromotionEvent::getExtraMoney()
{
	return extraMoney;
}

void PromotionEvent::Execute(Restaurant *pRest)
{

//Update after editing restaurant>>promote function
	
   pRest->PromoteOrder(OrderID, extraMoney, EventTime);
}

PromotionEvent::~PromotionEvent(void)
{
}
