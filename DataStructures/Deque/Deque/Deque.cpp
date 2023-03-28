#include "Deque.h"
#include<iostream>
using namespace std;                                             
///------------------------------------------------------
/// Default constructor
/// 
Deque::Deque() {
	noOfItems = 0;
	head = tail = NULL;
	
} //end-Deque

///------------------------------------------------------
/// Destructor
/// 
Deque::~Deque() {
	if (noOfItems != 0)
	{
		while (this->head)
		{
			DequeNode *node = this->head;
			this->head = this->head->next;
			delete node;
		}
	}
	
} //end-~Deque

///------------------------------------------------------
/// Adds a new item to the front of the Deque
/// 
void Deque::AddFront(int item) {
	DequeNode *newNode = new DequeNode(item);
	if (head == NULL)
		tail = head = newNode;
	else
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		/*if(noOfItems==1)
			cout << tail->item << endl;
		cout << head->item << endl;*/
		
	}
	noOfItems++;
} //end-AddFront

///------------------------------------------------------
/// Adds a new item to the end of the Deque
/// 
void Deque::AddRear(int item) {
	DequeNode *newNode = new DequeNode(item);
	if (tail == NULL)
		head = tail = newNode;
	else
	{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
	noOfItems++;
	
	//cout << tail->item << endl;
} //end-AddRear

///------------------------------------------------------
/// Remove and return the item at the front of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveFront() {
	if (IsEmpty())
		cout << " Deque is empty ."<<endl;

	DequeNode *temp = head;
	head = head->next;

	if (head == NULL)
	{
		tail = NULL;
	}

	int item = temp->item;
	delete(temp);
	noOfItems--;
	
	return item;
	
} //end-RemoveFront

///------------------------------------------------------
/// Remove and return the item at the rear of the Deque
/// If the Deque is empty, throw an exception
/// 
int Deque::RemoveRear() {
	if (IsEmpty())
		cout << "Deque is empty ."<<endl;
	DequeNode *temp = tail;
	tail = tail->prev;
	if (tail == NULL)
	{
		head = NULL;
	}
	int item = temp->item;
	delete(temp);
	noOfItems--;
	
	return item;
	
} //end-RemoveRear

///------------------------------------------------------
/// Return the item at the front of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Front() {
	if (IsEmpty())
		return -1;
	return head->item;
	
} //end-Front

///------------------------------------------------------
/// Return the item at the rear of the Deque (do not remove the item)
/// If the Deque is empty, throw an exception
/// 
int Deque::Rear() {
	if (IsEmpty())
		return -1;
	return tail->item;
	
} //end-Rear

