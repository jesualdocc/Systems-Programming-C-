#include <iostream>

template<typename T> 

void ReadAndPrint(const char *s) {

	std::cout << "Please Input a(n) " << s << "\n";
	T input;
	std::cin >> input;
	
	std::cout << "Input in Hex  = " << std::hex << input << "\n";
	std::cout << "Input in Decimal  = " << std::dec << input << "\n";


}

struct MyStruct
{
	int a;
};

int main() {

	MyStruct m;

	m.a = 6;

	ReadAndPrint<int>("int");
	ReadAndPrint<int64_t>("int64_t");
//	ReadAndPrint<MyStruct>("struct"); //- The function does not know how to handle that type (how to convert it to T)

	return 0;
}