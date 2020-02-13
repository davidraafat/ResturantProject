#include "CancellationEvent.h"

#include "..\Rest\Restaurant.h"


CancellationEvent::CancellationEvent(int time,int ID):Event(time ,ID)
{

}

void CancellationEvent::Execute(Restaurant *pRest)
{

//Update after editing restaurant>>promote function

	pRest->cancellNormal(OrderID,EventTime);

}

CancellationEvent::~CancellationEvent(void)
{
}
