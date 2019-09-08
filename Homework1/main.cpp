//Jesualdo Cristovao
// 01-11-2019
//Assignment 1

#include <iostream>

using namespace std;

int main() {
	
	int numbers[10];

	int arrayLength = sizeof(numbers) / sizeof(*numbers);

	cout <<"Please input "<< arrayLength << " numbers\n";

	//Populate array from user
	for (int i = 0; i < arrayLength; i++) {

		cin >> numbers[i];

	}
	//print array before sort
	cout << "Numbers before sort:";
	for (int i = 0; i < arrayLength; i++) {
		cout << " " << numbers[i];
	}

	cout << "\n";

	//Sort the array
	for (int i = 1; i < arrayLength; i++) {

		int temp = numbers[i];
		int j = i - 1;

		while (j >= 0 && numbers[j] > temp) {
			numbers[j + 1] = numbers[j];
			j--;
		}

		numbers[j + 1] = temp;
	}
	
	//print array after sort
	cout << "Numbers after sort:";
	for (int i = 0; i < arrayLength; i++) {
		cout << " " << numbers[i];
	}

	return 0;
}