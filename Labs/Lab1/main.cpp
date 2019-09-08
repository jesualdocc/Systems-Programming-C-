#include <iostream>
#include <string>

int main() {
	std::string name;
	std::cout << "Hello, what is your name? ";
	std::cin >> name;
	std::cout << "\n Greetings " << name << " from a C++ program.";

	return 0;
}