#ifndef __LinkedList__
#define __LinkedList__

#include <iostream>

//template<typename T>


template<typename T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList<T> &origList);
	bool isEmpty();
	void InsertAtHead(T item);
	T PeekHead();
	T RemoveHead();
	void PrintList();
	int Size();

private:
	int size;
	struct Node {
		T item;
		Node *next;
	};
	Node *headPtr;
	
	
};

//Default Constructor
template<typename T>
LinkedList<T>::LinkedList()
{
	headPtr = NULL;
	size = 0;
}

//Destructor
template<typename T>
LinkedList<T>::~LinkedList()
{
	for (Node *tmp = headPtr; isEmpty(); tmp = tmp->next) {
		delete tmp;
	}
}

//Copy Constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& origList)
{
	headPtr = NULL;

	for (Node *tmp = origList.headPtr; tmp != NULL; tmp = tmp->next) {
		InsertAtHead(tmp->item);
	}

}

template<typename T>
bool LinkedList<T>::isEmpty()
{
	return (size == 0);
}

template<typename T>
void LinkedList<T>::InsertAtHead(T item)
{
	Node *newNode = new Node;
	newNode->item = item;
	newNode->next = headPtr;
	headPtr = newNode;

	size++;
}

template<typename T>
T LinkedList<T>::PeekHead()
{
	return headPtr->item;
}

template<typename T>
T LinkedList<T>::RemoveHead()
{
	if (isEmpty()) {
		std::cout << "List is Empty \n";
		return NULL;
	}

	T itemRemoved = headPtr->item;

	Node *nodeRemoved = headPtr;

	headPtr = headPtr->next;

	delete nodeRemoved;

	size--;

	return itemRemoved;
}

template<typename T>
void LinkedList<T>::PrintList()
{
	for (Node *tmp = headPtr; tmp != NULL; tmp = tmp->next) {
		
		std::cout << tmp->item << "\n";
	}
}

template<typename T>
int LinkedList<T>::Size()
{
	return size;
}
#endif
