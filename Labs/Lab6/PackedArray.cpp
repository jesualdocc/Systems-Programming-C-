#include <iostream>

#include "PackedArray.h"

// Create the array; initialize memory
PackedArray CreateArray(int aSize)
{
	PackedArray arr;
	arr.rows = new uint64_t[aSize];
	arr.numRows = aSize;

	return arr;
}

// Frees memory for the array
void FreeArray(PackedArray &array)
{
	delete &array;
}

// Sets all entries in the array to value parameter
void FillArray(PackedArray &array, uint64_t value)
{
	for (int i = 0; i < array.numRows; i++) {
		for (int j = 0; j < 32; j++) {

			SetEntry(array, i, j, value);
			
		}
		
	}
}

// Clears all entries to 0 in the array
void ClearArray(PackedArray &array)
{
	for (int i = 0; i < array.numRows; i++) {
		*(array.rows + i) = 0;
	}
}

// Get the value of the entry at the specified row and col.
// If row or col are outside of the range for this PackedArray,
// returns 0.
int GetEntry(const PackedArray &array, int row, int col)
{
	
	if (row > array.numRows || row < 0 || col < 0 || col > 31) {
		return 0;
	}

	uint64_t temp = 3UL << (col * 2);
	uint64_t valueOfBits = *(array.rows + row) & temp;
	
	return (valueOfBits >> (col * 2));
}

// Sets entry in the location row, col to the specified value.
// If row or col are outside of the range for this PackedArray,
// function has no effect.
void SetEntry(PackedArray &array, int row, int col, uint64_t value)
{
	if (row > array.numRows || row < 0 || col < 0 || col > 31) {

		return ;
	}
	uint64_t temp = temp | (value << (col * 2));

	*(array.rows + row) = *(array.rows + row) | temp;
	
}

// Sum all the entries in the array
int SumEntries(const PackedArray &array)
{
	int sum = 0;
	for (int i = 0; i < array.numRows; i++) {
		for (int j = 0; j < 32; j++) {

			sum += GetEntry(array, i, j);
		}
	}
	return sum;
}