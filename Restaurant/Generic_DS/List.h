#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class List
{
	Node<T>* head;    //Pointer to the first element in the list
	Node<T>* tail;    //Pointer to the last element in the list
	Node<T>* getpointerto(T item);  //utility function to get pointer to specific data

public:
	


	List(void);
//	List(const List<T> & list );
	bool isEmpty();    
	bool insert(T newEntry);
	bool remove(T xItem);
	bool removehead(T &temp);
	T getentry(int pos);
	Node<T>* getNodeAt(int pos);
	Node<T>* getHead();
	void clear();
	~List(void);
};
///////////////////////////

template <typename T>
List<T>::List()
{
head=NULL;
tail=NULL;
}
template<class T>
Node<T>* List<T>::getNodeAt(int pos)
{
	Node<T>* nptr=head;
	if((pos>=1))
	{
	for(int i=1;i<pos;i++)
	{
		nptr=nptr->getNext();
	}
	return nptr;
	}
	else{return NULL;}
}

template <typename T>
T List<T>::getentry(int pos)
{
	if((pos>=1))
	{
		Node<T>* nptr=getNodeAt(pos);
		return nptr->getItem();
	}
	else{cout<<"entry not found";}
}
///////////////////////////
//template<typename T>
//List<T>::List(const List<T> & list )
//{
//	Node *tmp=list.head,*tail=NULL;
//	while(tmp)
//	{
//		if(tmp==list.head)
//		{
//			Node* added=new Node(tmp->getItem());
//			head=added;
//			tail=head;
//			tmp=tmp->getNext();
//		}
//		else
//		{
//			Node* added=new Node(tmp->getItem());
//			tail->setNext(added);
//			tail=added;
//			tmp=tmp->getNext();
//			
//		}
//		
//	}
//
//}

///////////////////////////

//check if the list is empty
template <typename T>
bool List<T>::isEmpty()
{
if (head==NULL)
    return true; 
return false;
}

///////////////////////////
//template <typename T>
//Node<T>* List<T>::getpointerto(T item)
//{
//	Node<T>*ptr=new Node;
//	ptr=head;
//while (ptr)
//{
//if(ptr->getItem()==item)
//	return ptr;
//else 
//	ptr=ptr->getNext();
//}
//return ptr->getNext();
//}
///////////////////////////
template <typename T>
bool List<T>::insert(T newEntry)
{
	if(head==NULL)
	{
	Node<T>*nNode=new Node<T>();
	if(nNode==NULL)
		return false;
	else
	{ 
	nNode->setNext(NULL);
	nNode->setItem(newEntry);
	head=nNode;
	tail=nNode;
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
	tail->setNext(nNode);
	tail=nNode;
	tail->setNext(NULL);
	return true;
	}
	
	}
}
///////////////////////////
template <typename T>
bool List<T>::remove(T xItem)
{

	Node<T>*prev=NULL;
	Node<T>*next=head;
	while(next)
	{
    if((next==head )&& ((next->getItem())==xItem))
	{
		head=head->getNext();
		delete next;
		return true;
	}
	else if((next->getItem())==xItem)
	{
	prev->setNext(next->getNext());
	delete next;
	return true;
	}
	else
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
	return false;
}
///////////////////////////
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

}

///////////////////////////
template <typename T>
bool List<T>::removehead(T &temp)
{
	if (head==NULL) return false;
	
	Node<T>*next=head;
	temp=next->getItem();
		head=head->getNext();
		delete next;
		return true;
	

}

///////////////////////////
template <typename T>
List<T>::~List()
{
clear();
}
template <typename T>

	Node<T>* List<T>::getHead()
	{return head;}