#pragma once
#include "Events\Event.h"

class PromotionEvent:public Event
{
	int ExtraMon;
public:
	PromotionEvent(int ,int ,int);
	virtual void Execute(Restaurant* pRest);
	~PromotionEvent(void);
};

