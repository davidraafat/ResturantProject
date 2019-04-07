#pragma once
#include "PriorityNode.h"

template <typename T>
class ProQueue
{
private :
	
	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
public :
	ProQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,float p);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;	
	~ProQueue();

};

//////////////////////////

template <typename T>
ProQueue<T>::ProQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;

}

//////////////////////////

template <typename T>
bool ProQueue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}
//////////////////////////
template <typename T>
bool ProQueue<T>::enqueue(const T& newEntry,float p)
{   
	PriorityNode<T>*newnode=new PriorityNode<T>;
	if(newnode==NULL) return false;
	
	else if(frontPtr)
	{    newnode->setItem(newEntry);
	     newnode->setpriority(p);
		PriorityNode<T> *ptr=frontPtr;
		while (ptr->getNext()&&(ptr->getpriority()>=newnode->getpriority()))	
		{
			ptr =ptr->getNext();
		}
	  if (ptr==frontPtr)
		  { 
			  if (ptr->getpriority()>=newnode->getpriority())
				  {
					newnode->setNext(ptr->getNext());
					ptr->setNext(newnode);
					return true;
				  }
			  else
				  {
					  newnode->setNext(ptr);
					  frontPtr=newnode;
					  return true;
				  }
		  }
	  else
	  {   
		newnode->setNext(ptr->getNext());
		ptr->setNext(newnode);
		return true;
	  }
	}

	else
	{
		newnode->setItem(newEntry);
      	newnode->setpriority(p);
		frontPtr=newnode;
		backPtr=newnode;
		backPtr->setNext(NULL);
		return true;
	}
}
//////////////////////////
template <typename T>
bool ProQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	PriorityNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}
/////////////////////////////
template <typename T>
bool ProQueue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
	return false;

	frntEntry = frontPtr->getItem();
	return true;

}
/////////////////////////////
template <typename T>
ProQueue<T>::~ProQueue()
{
}

