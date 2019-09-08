#ifndef __LinkedList__
#define __LinkedList__

#include <iostream>
#include "Node.h"

class LinkedList {
public:
	LinkedList();
	void InsertAtHead(int v);
	void PrintList();
	void freeList();
private:
	Node *HeaderP;
};



#endif
