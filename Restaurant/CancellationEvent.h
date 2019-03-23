#pragma once
#include "Events\Event.h"

class CancellationEvent:public Event
{
	
public:
	CancellationEvent(int time,int id);
	~CancellationEvent(void);
	virtual void Execute(Restaurant* pRest);
};

