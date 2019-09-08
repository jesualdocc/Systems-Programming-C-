#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "MyString.h"
#include <cstdio>

MyString::MyString()
{
	string = new char[1];
	string[0] = '\0';
}

MyString::MyString(const MyString& s)
{
	string = new char[s.length() + 1];
	for (int i = 0; i < s.length(); i++)
	{
		string[i] = s.string[i];
	}
	string[s.length()] = '\0';

}

MyString::MyString(const char *s)
{
	string = new char[strlen(s) + 1];

	for (int i = 0; i < strlen(s); i++)
	{
		string[i] = s[i];
	}
	string[strlen(s)] = '\0';

}

MyString::~MyString()
{
	delete[] string;
	string = NULL;
}

MyString& MyString::operator=(const MyString& s)
{
	if (this == &s) return *this;

	string = new char[s.length() + 1];
	for (int i = 0; i < s.length(); i++)
	{
		string[i] = s.string[i];
	}
	string[s.length()] = '\0';

	return *this;

}

MyString & MyString::operator+=(const MyString &rhs)
{
	// TODO: insert return statement here
	char *tmp = new char[length() + rhs.length() + 1]; // Allocate memory for new string

	strcpy(tmp, string);

	delete[] string; //Delete old string after being copied

	strcat(tmp, rhs.cString()); //Concatenates string

	string = tmp;

	tmp = NULL;

	return *this;
}

char MyString::operator[](size_t i) const
{
	char c = ' ';
	if (i >= length()) {

		c = '\0';
	}
	else {
		c = string[i];
	}
	
	return c;
}

char & MyString::operator[](size_t i)
{
	if (i >= length()) {

		return string[length()];
	}

	return string[i];
}

size_t MyString::length() const
{
	return strlen(string);
}

const char* MyString::cString() const
{
	return string;
}

MyString operator+(const MyString & s1, const MyString & s2)
{
	MyString newString;

	newString += s1;
	newString += s2;

	return newString;
}

std::ostream & operator<<(std::ostream & os, const MyString & s)
{
	os << s.cString();

	return os;
}
