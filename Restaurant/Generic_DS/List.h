#pragma once
#include "Node.h"
#include <iostream>

template <typename T>
class List
{
	Node<T>* head;    //Pointer to the first element in the list
	Node<T>* tail;    //Pointer to the last element in the list
	//Node<T>* getpointerto(T item);  //utility function to get pointer to specific data

public:
	List(void);
//	List(const List<T> & list );
	bool isEmpty();    
	bool insert(Node<T>*newEntry);
	bool remove(T xItem);
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
bool List<T>::insert(Node<T>*newEntry)
{
	if(head==NULL)
	{
	Node<T>*nNode=new Node;
	if(nNode==NULL)
		return false;
	else
	{ 
	nNode->setNext(NULL);
	nNode->setItem(newEntry->getItem());
	head=nNode;
	tail=nNode;
	return true;
	}
	
	}
	else 
	{
	Node<T>*nNode=new Node;
	if(nNode==NULL)
		return false;
	else
	{
	tail->setNext(nNode);
	tail=nNode;
	tail->setNext(NULL);
	return true;
	}
	
	}}
///////////////////////////
template <typename T>
bool List<T>::remove(T xItem)
{
	Node<T>*prev=NULL;
	Node<T>*next=head;

	while(next)
	{
    if(next==head && next->getItem()==xItem)
	{
		head=head->getNext();
		delete next;
		return true;
	}
	else if(next->getItem()==xItem)
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
List<T>::~List()
{
clear();
}