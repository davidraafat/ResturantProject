#include "PromotionEvent.h"
#include"Rest\Restaurant.h"

PromotionEvent::PromotionEvent(int time ,int id,int extMo):Event(time,id)
{

	ExtraMon=extMo;
}
 void PromotionEvent::Execute(Restaurant* pRest)
 {
	 pRest->PromoteOrder(OrderID,ExtraMon);
 
 }
PromotionEvent::~PromotionEvent(void)
{
}
