#pragma once
#include "PriorityNode.h"

template <typename T>
class ProQueue
{
private :
	
	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
	int count;
public :
	ProQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,double p);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	const T* toArray() const ; 
	~ProQueue();

};

//////////////////////////

template <typename T>
ProQueue<T>::ProQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
	count=0;
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
bool ProQueue<T>::enqueue(const T& newEntry,double p)
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
					count++;
					return true;
				  }
			  else
				  {
					  newnode->setNext(ptr);
					  frontPtr=newnode;
					  count++;
					  return true;
				  }
		  }
	  else
	  {   
		newnode->setNext(ptr->getNext());
		ptr->setNext(newnode);
		count++;
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
		count++;
		return true;
	}
}
//////////////////////////
template <typename T>
bool ProQueue<T>:: dequeue(T & frntEntry)  
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

	count--;
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
//////////////////////////////
template <typename T>
const T * ProQueue<T>::toArray() const
{
	T * Contents= new T [count];
	PriorityNode<T>* curPtr = frontPtr;
	int counter = 0;
	while (curPtr != nullptr&& (counter < count))
	{
		
		Contents[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	return Contents;
} // end toArray
/////////////////////////////
template <typename T>
ProQueue<T>::~ProQueue()
{
	while(!isEmpty())
	{
		T item;
		dequeue(item);
	}
}
