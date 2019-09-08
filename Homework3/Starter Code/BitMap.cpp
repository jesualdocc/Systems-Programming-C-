/*
 *  BitMap.cpp
 *  HW 3
 */

#include "BitMap.h"
#include <stdio.h>
#include <iostream>

BitMap *CreateBitMapPic(int width, int height)
{
}

void Free(BitMapPointer &bm)
{
}

void SetPixel(BitMap *bm, int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte)
{
}

void GetPixel(BitMap *bm, int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte)
{
}


void Save(BitMap *bm, const char *file)
{
	// 1. Open the file
	
	// 2. Create a header and write it to the file
	
	// 3. Write the bitmap data to the file

	// 4. Close the file
}

BitMap *Load(const char *file)
{
	// 0. If any of the operations fail, free any memory and return 0

	// 1. Open the file
	
	// 2a. Read the initial fields of the header; verify that the file type (BM) is correct.
	// 2b. Read the rest of the header.
	
	// 3. Verify if the file is 24 or 32 bits.
	
	// 4. Check if the rows are stored in reverse order (due to negative height)

	// 5. Make sure the file isn't compressed (compression should be 0)

	// 6. Load the file if it is 32 bits
	// 6a. If the file is 32 bits, you can read one row at a time.
	// 6b. If the height is negative, you need to read from disk into the rows in memory in reverse order
	// 6c. 32-bit files are never padded.

	// 7. Load the file if it is 24 bits
	// 7a. If the file is 24 bits, you need to read 3 bytes at a time and make space in memory for
	//     the extra byte. (Since your internal storage should always be 32 bits.)
	// 7b. If the height is negative, you need to read from disk into the rows in memory in reverse order
	// 7c. If the length of each line isn't divisible by 4, you need to read extra padding from the file.
	//     This padding shouldn't be stored in the bitmap data in memory.

	// 8. Close the file.
	// 9. Return a pointer to the bitmap.
}

