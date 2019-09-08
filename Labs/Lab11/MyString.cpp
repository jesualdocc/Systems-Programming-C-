
#include "MyString.h"
#include <iostream>

//Default Constructor
MyString::MyString() {
	string = new char;
	*string = '\0';
}

//Copy Constructor
MyString::MyString(const MyString &s)
{
	int length = strlen(s.string);
	string = new char[length + 1];
	
	for (int i = 0; i < length; i++) {
		string[i] = (s.string)[i];
	}
	string[length] = '\0';
}

MyString::MyString(const char *s) {
	
	int length = strlen(s);

	string = new char[length + 1];
	
	for (int i = 0; i < length; i++) {
		string[i] = s[i];
	}
	string[length] = '\0';
	
}

//Assignment operator
MyString& MyString::operator=(const MyString &s) {
	int length = strlen(s.string);
	
	if (this != &s) { // 1. Don't self-assign
		delete string; // 2. Delete old string
		string = new char[length + 1]; //Allocate new string
	
		for (int i = 0; i < length; i++) {
			string[i] = (s.string)[i];
		}
		string[length] = '\0';
	}

	return *this;
}

MyString::~MyString() {
	delete[] string;

}

size_t MyString::length() const {
	return strlen(string);
}


const char * MyString::cString() const {
	return string;
}