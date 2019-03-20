#include "VIPorders.h"


VIPorders::VIPorders(int id, ORD_TYPE r_Type, REGION r_region):Order(id, r_Type, r_region)
{

}

void VIPorders::setpriority()
{
	//ToDO put a function to calculate priorty
//if(pro>0)
//	priority=pro;
//else
//	priority=1;
}

///////////////

int  VIPorders::getpriority()
{
	return priority;
}

VIPorders::~VIPorders(void)
{
}
