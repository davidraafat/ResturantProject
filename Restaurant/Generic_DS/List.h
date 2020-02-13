#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class List
{
	Node<T>* head;    //Pointer to the first element in the list
	Node<T>* tail;    //Pointer to the last element in the list
	int count;        //it will be used @ to array function

public:
	List(void);                                              //Constructor 
	List(const List<T> & list );                             //Copy Constructor  
	bool isEmpty();                                          //check if the list is empty
	bool insert(T newEntry);                                 //Insetat the end of the list
	bool insertpos(int newPosition,const T& newEntry);       //insert in specific Position
	bool remove(T & xItem);             //To remove specific element
	bool removehead(T &temp);           //To remove the first element
	void clear();                       // Clear the list & delete all elements in it
	Node<T>* getNodeAt(int );           //Get pointer to item in specific position
	const T * toArray() const ;
	~List(void);                        //Distructor   
};
///////////////////////////

template <typename T>
List<T>::List()
{
head=NULL;
tail=NULL;
count=0;
}
///////////////////////////
template<typename T>
List<T>::List(const List<T> & list )
{
	Node *tmp=list.head,*tail=NULL;
	count=list.count;
	while(tmp)
	{
		if(tmp==list.head)
		{
			Node* added=new Node(tmp->getItem());
			head=added;
			tail=head;
			tmp=tmp->getNext();
		}
		else
		{
			Node* added=new Node(tmp->getItem());
			tail->setNext(added);
			tail=added;
			tmp=tmp->getNext();
			
		}
		
	}

}

///////////////////////////
//check if the list is empty
template <typename T>
bool List<T>::isEmpty()
{
if (head==NULL)
    return true; 
return false;
}

/////////////////////////
template <typename T>
bool List<T>::insert(T newEntry)
{
	if(head==NULL)
		{
		Node<T>*nNode=new Node<T>;
		if(nNode==NULL)  return false;

		else
			{ 
				nNode->setNext(NULL);
				nNode->setItem(newEntry);
				head=nNode;
				tail=nNode;
				count++;
				return true;
			}
	
		}
	else 
		{
		Node<T>*nNode=new Node<T>;
			if(nNode==NULL)
				return false;
			else
				{
					nNode->setItem(newEntry);
					tail->setNext(nNode);
					tail=nNode;
					tail->setNext(NULL);
					count++;
					return true;
				}
	
		}
}
////////////////////////////////////

template <typename T>
bool List<T>::insertpos( int newPosition,const T & newEntry)
{
	bool ableToInsert = (newPosition >= 1);
	if (ableToInsert)
	{
	// Create a new node containing the new entry
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Attach new node to chain
		if (newPosition == 1)
			{
			// Insert new node at beginning of chain
			newNodePtr->setNext(head);
			head = newNodePtr;
			count++;
			}
		else
			{
			// Find node that will be before new node
			Node<T>* prevPtr = getNodeAt(newPosition - 1);
			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
			count++;
			} // end if

	} // end if
return ableToInsert;
} // end insert

/////////////////////////////////////
template<class T>
Node<T>* List<T>::getNodeAt(int pos)
{
	Node<T>* nptr = head;
	if ((pos >= 1))
	{
		for (int i = 1; i<pos; i++)
		{
			nptr = nptr->getNext();
		}
		return nptr;
	}
	else
	{
		return NULL;
	}
}

////////////////////////
template <typename T>
bool List<T>::remove(T & xItem)
{
	Node<T>*prev=NULL;
	Node<T>*next=head;

	while(next)
	{
    if(next==head && (next->getItem())==xItem)
		{
			head=head->getNext();
			delete next;
			count--;
			return true;
		}
	else if(next->getItem()==xItem)
		{
		if (next == tail)
		{
			tail = prev;
		}
		prev->setNext(next->getNext());
		delete next;
		count--;
		return true;
		}
	else
		{
		if(next == head)
			{
				next=next->getNext();
				prev=head;
			}
			else
			{
			next=next->getNext();
			prev=prev->getNext();
			}
		}
	}
	return false;
}
///////////////////////////////
template <typename T>
void List<T>::clear()
{
	Node<T> *P = head;
	while (head != NULL)
	{
		P = head->getNext();
		delete head;
		head = P;
	}
	count=0;
}

///////////////////////////
template <typename T>
bool List<T>::removehead(T &temp)
{
	if (head==NULL) return false;

	if(head==tail)
	{
		temp = head->getItem();
		delete head;
       	head=tail=nullptr;
		count--;
		return true;
	}
	else
	{
      	Node<T>*next=head;
	    temp=next->getItem();
		head=head->getNext();
		
		delete next;
		count--;
		return true;
	}

}
///////////////////////////
template < typename T>
const T * List<T>::toArray() const
{
	T * Contents= new T [count];
	Node<T>* curPtr = head;
	int counter = 0;
	while (curPtr != nullptr&& (counter < count))
	{
		Contents[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	return Contents;
} // end toArray
///////////////////////////
template <typename T>
List<T>::~List()
{
clear();
}
