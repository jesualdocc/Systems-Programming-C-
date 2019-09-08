#define _CRT_SECURE_NO_WARNINGS

#include "ExpandableArray.h"
#include <string.h>

//Default no parameter constructor
ExpandableArray::ExpandableArray()
{
	maxSize = 16;
	currentIndex = 0;
	theArray = new char*[maxSize]; //Alocates memory for 16 strings of unknown length
}

//Default size parameter constructor
ExpandableArray::ExpandableArray(int initialSize)
{
	maxSize = initialSize;
	currentIndex = 0;
	theArray = new char*[maxSize];
}

ExpandableArray::~ExpandableArray()
{
	for (int i = 0; i < length(); i++) {
		delete[] theArray[i]; // Destroys memory allocated for length of each string
	}

	delete[] theArray; // Destroys memory allocated for each string

	theArray = NULL;
}

void ExpandableArray::Append(char * element)
{
	if (currentIndex == maxSize) { //Maximum Reached
		ExpandArray();
	}

	//Index is already pointing to a location in the new allocated memory
	theArray[currentIndex] = new char[strlen(element) + 1]; //Allocate enought memory for string

	strcpy(theArray[currentIndex], element);
	
	currentIndex++;
}

void ExpandableArray::Sort()
{
	for (int i = 0; i < length(); i++) {
		for (int j = i + 1; j < length(); j++) {
			if (strlen(theArray[i]) < strlen(theArray[j])) {
				//Swap Longest to Shortest
				char *tmp = theArray[i];
				theArray[i] = theArray[j];
				theArray[j] = tmp;
			}
		}
	}
}

int ExpandableArray::length()
{
	return currentIndex;
}

char * ExpandableArray::get(int i)
{
	return theArray[i];
}

void ExpandableArray::ExpandArray()
{
	maxSize = maxSize * 2; //Doubles the size of array

	char **newArray = new char*[maxSize]; //Allocate memory for a larger array

	//Copy elements from old array into the new, larger one
	// Number of elements in old array given by length()
	for (int i = 0; i < length(); i++) {
		newArray[i] = theArray[i]; //Takes the pointers of the string in the old array
	}
	
	delete[] theArray; //Delete old array
	theArray = newArray; //Replaces the old array by the new one
}
