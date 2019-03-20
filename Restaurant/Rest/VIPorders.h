#pragma once
#include "Order.h"
class VIPorders:public Order
{
	int priority;
public:

	void setpriority();
	int getpriority();
	VIPorders(int id, ORD_TYPE r_Type, REGION r_region);
	~VIPorders(void);
};

