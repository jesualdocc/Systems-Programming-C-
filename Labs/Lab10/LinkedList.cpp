#include "LinkedList.h"
#include "Node.h"
#include <iostream>

	LinkedList::LinkedList() {
		HeaderP = NULL;
	}

	void LinkedList::InsertAtHead(int v) {
		Node *newNode = new Node;
		newNode->SetValue(v);
		newNode->SetNext(HeaderP);
		HeaderP = newNode;
	}
	void LinkedList::PrintList() {
		Node *tmp = HeaderP; // 
		while (tmp != NULL) {
			std::cout << tmp->GetValue() << " ";
			tmp = tmp->GetNext();
		}
		std::cout << "\n";
	}

	void LinkedList::freeList() {
		Node *tmp;
		while (HeaderP != NULL) {
			tmp = HeaderP->GetNext();
			delete HeaderP;
			HeaderP = tmp;
		}

	}