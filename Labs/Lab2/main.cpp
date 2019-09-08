//Jesualdo Cristovao

#include <iostream>

int main() {

	//-------1

	std::cout << "Size of bool is " << sizeof(bool) << " byte(s) \n";
	std::cout << "Size of char is " << sizeof(char) << " byte(s) \n";
	std::cout << "Size of short is " << sizeof(short) << " byte(s) \n";
	std::cout << "Size of int is " << sizeof(int) << " byte(s) \n";
	std::cout << "Size of long is " << sizeof(long) << " byte(s) \n";
	std::cout << "Size of long long is " << sizeof(long long) << " byte(s) \n";
	std::cout << "Size of float is " << sizeof(float) << " byte(s) \n";
	std::cout << "Size of double is " << sizeof(double) << " byte(s) \n";
	std::cout << "Size of long double is " << sizeof(long double) << " byte(s) \n";
	std::cout << "Size of int8_t is " << sizeof(int8_t) << " byte(s) \n";
	std::cout << "Size of int16_t is " << sizeof(int16_t) << " byte(s) \n";
	std::cout << "Size of int32_t is " << sizeof(int32_t) << " byte(s) \n";
	std::cout << "Size of int64_t is " << sizeof(int64_t) << " byte(s) \n\n\n";


	//-------2

	int16_t n16;
	int32_t n32;
	int64_t n64;

	std::cout << "Enter a Number 3 times\n";
	std::cin >> n16 >> n32 >>n64;
	std::cout << "Decimal --> int16_t = " << std::dec << n16 << "        int32_t = " << std::dec << n32 << "         int64_t = " << std::dec << n64 << "\n";
	std::cout << "Hex --> int16_t = " << std::hex << n16 << "        int32_t = " << std::hex << n32 << "         int64_t = " << std::hex << n64 << "\n";

	//-----3

	int a = 0xFFFFFFFFFF; //10 Fs = 40 bits --> int is signed 32bits
	int b = a + 0x01;

	std::cout << "Value of a: " << a << "\n"; //Only 8Fs are printed
	std::cout << "Value of b: " << b << "\n";

	//--------4

	uint32_t min32 = 0x00;
	uint32_t max32 = 0xFFFFFFFF;
	uint64_t min64 = 0x00;
	uint64_t max64 = 0xFFFFFFFFFFFFFFFF;

	std::cout << "Min uint32_t = " << min32 << " Max uint32_t = " << max32 << " \n";
	std::cout << "Min uint64_t = " << min64 << " Max uint64_t = " << max64 << " \n\n";

	//---------5

	int32_t mi32 = 0x80000000;
	int32_t ma32 = 0x7FFFFFFF;
	int64_t mi64 = 0x8000000000000000;
	int64_t ma64 = 0x7FFFFFFFFFFFFFFF;

	std::cout << "Min int32_t = -" << mi32 << " Max int32_t = " << ma32 << " \n";
	std::cout << "Min int64_t = -" << mi64 << " Max int64_t = " << ma64 << " \n";


	//------6

	//Compilation Error
	//int x;
	//float f;

	//std::cout << "Unitialized Integer: " << x ;
	//std::cout << "\n Unitialized Float : " << f << "\n";

	return 0;
}