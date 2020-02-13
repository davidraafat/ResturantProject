#pragma once
#include "Event.h"
class CancellationEvent:public Event
{

public:

	CancellationEvent(int time,int ID);
	virtual void Execute(Restaurant *pRest);
	~CancellationEvent(void);
};

