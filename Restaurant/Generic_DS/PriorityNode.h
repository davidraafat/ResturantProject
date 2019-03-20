#pragma once
#include "Node.h"
template <typename T>
class PriorityNode:public Node<T>
{

	int priority;

public:
	PriorityNode(void);
	void setpriority(int pro);
	int getpriority();
	~PriorityNode(void);
};



///////////////
template <typename T>
void PriorityNode<T>::setpriority(int pro)
{
if(pro>0)
	priority=pro;
else
	priority=1;
}

///////////////
template <typename T>
int PriorityNode<T>::getpriority()
{
	return priority;
}