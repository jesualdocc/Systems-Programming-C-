#include <iostream>
#include <chrono>
#include <ctime>


struct pair {

	int a;
	int b;
};

struct Struct {
	int array[1000];
};

int addAll_value(Struct s) {

	int sum = 0;
	int arraySize = sizeof(s.array)/sizeof(*(s.array));

	for (int i = 0; i < arraySize; i++) {
		
		sum += s.array[i];
	}

	return sum;
}

int addAll_reference(const Struct &s) {
	int sum = 0;

	for (int i = 0; i < (sizeof(int) / sizeof(s.array)); i++) {
		sum += s.array[i];
	}

	return sum;
}

void swap_value(int a, int b) {

	int temp = a;
	a = b;
	b = temp;
}

void swap_value(pair p) {
	int temp = p.a;
	p.a = p.b;
	p.b = temp;
}

void swap_reference(int &a, int &b) {

	int temp = a;
	a = b;
	b = temp;
}

void swap_reference(pair &p) {

	int temp = p.a;
	p.a = p.b;
	p.b = temp;
}

void swap_pointer(int *a, int *b) {

	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap_pointer(pair *p) {

	int temp = p->a;
	p->a = p->b;
	p->b = temp;
}

int main() {

	std::cout << "Part 1 \n\n";
	int a = 10;
	int b = 20;

	std::cout << "Before swap_value is called, a = " << a << " b = " << b << " \n";
	swap_value(a, b);
	std::cout << "After swap_value is called, a = " << a << " b = " << b << " \n\n";
	//pass by value doesn't do the swap

	std::cout << "Before swap_reference is called, a = " << a << " b = " << b << " \n";
	swap_reference(a, b);
	std::cout << "After swap_reference is called, a = " << a << " b = " << b << " \n\n";

	std::cout << "Before swap_pointer is called, a = " << a << " b = " << b << " \n";
	swap_pointer(&a, &b);
	std::cout << "After swap_pointer is called, a = " << a << " b = " << b << " \n\n";

	//-----------------------------------------------------------------------------------------------
	//Part 2

	std::cout << "Part 2 \n\n";

	pair pairS;
	pairS.a = 10;
	pairS.b = 20;

	std::cout << "Before swap_value is called, a = " << pairS.a << " b = " << pairS.b << " \n";
	swap_value(pairS);
	std::cout << "After swap_value is called, a = " << pairS.a << " b = " << pairS.b << " \n\n";
	//pass by value doesn't do the swap

	std::cout << "Before swap_reference is called, a = " << pairS.a << " b = " << pairS.b << " \n";
	swap_reference(pairS);
	std::cout << "After swap_reference is called, a = " << pairS.a << " b = " << pairS.b << " \n\n";

	std::cout << "Before swap_pointer is called, a = " << pairS.a << " b = " << pairS.b << " \n";
	swap_pointer(&pairS);
	std::cout << "After swap_pointer is called, a = " << pairS.a << " b = " << pairS.b << " \n\n";

	//----------------------------------------------------------------------------------------------
	//Part 3

	std::cout << "Part 3 \n\n";

	Struct s;

	for (int i = 0; i < 1000 ; i++) {

		s.array[i] = i * 2;
	}

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	for (int i = 0; i < 10000; i++) {
		addAll_value(s);
	}

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Elapsed time by Value: " << elapsed_seconds.count() << "s\n";

	std::chrono::time_point<std::chrono::system_clock> start2, end2;
	start2 = std::chrono::system_clock::now();

	for (int i = 0; i < 10000; i++) {
		addAll_reference(s);
	}

	end2 = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
	std::cout << "Elapsed time by reference: " << elapsed_seconds2.count() << "s\n";


	return 0;
}