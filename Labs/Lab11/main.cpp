#include <iostream>
#include "MyString.h"

int main(int argc, const char * argv[])
{
	MyString s;
	std::cout << "Empty: '" << s.cString() << "'\n";
	s = "hello";
	std::cout << "After operator=: '" << s.cString() << "'\n";
	{
		MyString t(s);
		std::cout << "After copy: '" << t.cString() << "'\n";
		s = t;
	}

	MyString m(" world");
	std::cout << "After constructor: '" << m.cString() << "'\n";
	m = s;
	std::cout << "After operator=: '" << m.cString() << "'\n";
	m = m;
	std::cout << "After operator=: '" << m.cString() << "'\n";

	return 0;
}