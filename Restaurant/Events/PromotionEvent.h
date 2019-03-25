#pragma once

#include "Event.h"

class PromotionEvent:public Event
{
	double extraMoney;

public:
	PromotionEvent(int time,int ID,double extra);
	double getExtraMoney();
	virtual void Execute(Restaurant *pRest);
	~PromotionEvent(void);
};

