#pragma once

#include <iostream>

class MyString {
public:
	MyString();
	MyString(const MyString &);
	MyString(const char *);
	~MyString();
	MyString &operator=(const MyString &);
	MyString &operator+=(const MyString &);
	char operator[](size_t i) const;
	char &operator[](size_t i);
	size_t length() const;
	const char *cString() const;
private:
	char *string;
	size_t stringLength;  // not required, but handy to keep around
	// You may add helper functions here if desired
};

MyString operator+(const MyString &s1, const MyString &s2);

std::ostream& operator<<(std::ostream& os, const MyString& s);
