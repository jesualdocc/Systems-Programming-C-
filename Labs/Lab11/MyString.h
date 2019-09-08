#pragma once

class MyString {
public:
	MyString();
	MyString(const MyString &s);
	MyString(const char *s);
	~MyString();
	MyString &operator=(const MyString &s);
	size_t length() const;
	const char *cString() const;
private:
	char *string;
};
