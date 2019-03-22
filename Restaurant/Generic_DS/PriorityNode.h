#pragma once
#include "Node.h"
template <typename T>
class PriorityNode:public Node<T>
{
private:
	float priority;
public:
	PriorityNode();
	void setpriority(float pro);
    float getpriority();
	PriorityNode<T>* getNext() const;
	~PriorityNode();
};

///////////////
template <typename T>
void PriorityNode<T>::setpriority(float pro)
{
if(pro>0)
	priority=pro;
else
	priority=1;
}

///////////////
template <typename T>
float PriorityNode<T>::getpriority()
{
	return priority;
}
template <typename T>
PriorityNode<T>* PriorityNode<T>:: getNext() const 
{
	PriorityNode<T>* next=getNext();
	return next;
}
template <typename T>
PriorityNode<T>::PriorityNode<T>(){}
template <typename T>
PriorityNode<T>::~PriorityNode<T>(){}