#include "CancellationEvent.h"
#include "Rest\Restaurant.h"


CancellationEvent::CancellationEvent(int time,int id):Event(time,id)
{
}
void CancellationEvent::Execute(Restaurant* pRest)
{
	pRest->cancellNormal(OrderID);
}
CancellationEvent::~CancellationEvent(void)
{
}
