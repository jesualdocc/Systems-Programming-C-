#include <iostream>
#include "LinkedList.h"
#include <string>

int main() {

	LinkedList<uint64_t> listInt;

	listInt.InsertAtHead(0);
	listInt.InsertAtHead(1);
	listInt.InsertAtHead(2);
	listInt.InsertAtHead(3);
	listInt.InsertAtHead(4);

	LinkedList<std::string> listString;
	listString.InsertAtHead("Hello");
	listString.InsertAtHead("World");


	listInt.PrintList();
	listString.PrintList();

	return 0;
}