#pragma once
#include "Order.h"
#include "Motorcycle.h"
#include "VIPorders.h"
#include "\DataProject\Project_Code_S2019\Restaurant\Generic_DS\List.h"
#include "\DataProject\Project_Code_S2019\Restaurant\Generic_DS\Queue.h"
#include "\DataProject\Project_Code_S2019\Restaurant\Generic_DS\ProQueue.h"

class Region
{
	List<Order> normalOrders; 
	Queue<Order> frozenOrders;
	ProQueue<VIPorders> vipOrders; 
	
	

public:
	Region(void);
	~Region(void);
};

