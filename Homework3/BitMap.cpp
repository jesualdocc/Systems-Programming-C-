/*
 *  BitMap.cpp
 *  HW 3
 */
#define _CRT_SECURE_NO_WARNINGS

#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>

BitMap *CreateBitMapPic(int width, int height)
{
	if (width < 0 ) {
		std::cout << " Width must be Positive";
		return 0;
	}
	
	int h = abs(height);

	BitMapPointer bm = new BitMap;
	bm->width = width;
	bm->height = h;
	bm->image = new uint8_t[width * h * 4];
	
	return bm;

}

void Free(BitMapPointer &bm)
{
	delete bm;
}

void SetPixel(BitMap *bm, int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte)
{
	//BitMap *tmp = bm;
	//B-G-R-A (Order from instructions)
	
	bm->image[4 * (x + y * bm->width)] = blueByte; //[0]
	bm->image[(4 * (x + y * bm->width)) + 1] = greenByte; //[1]
	bm->image[(4 * (x + y * bm->width)) + 2] = redByte; //[2]
	bm->image[(4 * (x + y * bm->width)) + 3] = alphaByte; //[3]
	
}

void GetPixel(BitMap *bm, int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte)
{
	blueByte = bm->image[4 * (x + y * bm->width)]; //[0]
	greenByte = bm->image[4 * (x + y * bm->width) + 1]; //[1]
	redByte = bm->image[4 * (x + y * bm->width) + 2]; //[2]
	alphaByte = bm->image[4 * (x + y * bm->width) + 3];//[3]
}


void Save(BitMap *bm, const char *file)
{
	// 1. Open the file

	FILE * outFile;
	outFile = fopen(file, "wb+");
	
	// 2. Create a header and write it to the file

	uint16_t signatureField = 19778;

	int returnValue = fwrite(&signatureField, sizeof(signatureField), 1, outFile);

	if (returnValue != 1) { // 1 is count value
		std::cout << "Error Writing File!! \n";
	}

	BitMapHeader *fileHeader = new BitMapHeader();
	
	fileHeader->biHeight = bm->height;
	fileHeader->biWidth = bm->width;
	
	returnValue = fwrite(fileHeader, sizeof(BitMapHeader), 1, outFile);

	if (returnValue != 1) { // 1 is count value
		std::cout << "Error Writing File!! \n";
	}
	
	int count = bm->height * bm->width * 4;
	// 3. Write the bitmap data to the file
	
	returnValue = fwrite(bm->image, sizeof(*bm->image), count, outFile);

	if (returnValue != count) { // 1 is count value
		std::cout << "Error Writing File!! \n";
	}

	// 4. Close the file
	fclose(outFile);
}

BitMap *Load(const char *file)
{
	// 0. If any of the operations fail, free any memory and return 0

	// 1. Open the file
	
	FILE *inFile = fopen(file, "rb+");

	if (inFile == NULL) {
		std::cout << "Error!! File Not Found\n";
		delete inFile;
		return 0;
	}

	// 2a. Read the initial fields of the header; verify that the file type (BM) is correct.

	uint16_t *signatureField = new uint16_t;

	int returnValueRead = fread(signatureField, sizeof(*signatureField), 1, inFile);

	if (returnValueRead != 1) { // 1 is count value
		std::cout << "Error Reading File!! \n";
		delete signatureField;
		return 0;
	}

	if (!(*signatureField == 19778)) {
		std::cout << "Error!! Not a BM File\n";
		delete signatureField;
		return 0;
	}

	// 2b. Read the rest of the header.

	BitMapHeader fileHeader;
	fread(&fileHeader, sizeof(fileHeader), 1, inFile);

	// 3. Verify if the file is 24 or 32 bits.
	uint32_t bitsPerPixel = fileHeader.biBitCount;


	// 4. Check if the rows are stored in reverse order (due to negative height)

	uint32_t width = fileHeader.biWidth;
	int height = (int32_t)fileHeader.biHeight;

	bool isReversed = height < 0;
	
	// 5. Make sure the file isn't compressed (compression should be 0)

	uint32_t compression = fileHeader.biCompression;

	if (!(compression == 0)) {
		delete signatureField;
		return 0;
	}


	int h = abs(height);

	BitMapPointer bm = CreateBitMapPic(width, h);

	// 6. Load the file if it is 32 bits
	// 6a. If the file is 32 bits, you can read one row at a time.
	// 6b. If the height is negative, you need to read from disk into the rows in memory in reverse order
	// 6c. 32-bit files are never padded.

	if (bitsPerPixel == 32) {
		fseek(inFile, fileHeader.bfOffBits, SEEK_SET);
		if (isReversed) {
			for (int i = h - 1; i >= 0; i--) {
				//Start Filling from the top row, (width * 4) bytes for each row
				fread(&bm->image[4 * width * i], sizeof(*bm->image) * 4, width, inFile);
			}
		}
		else {
			for (int i = 0; i < h; i++) {
				//Start Filling from the bottom row, (width * 4) bytes for each row

				fread(&bm->image[4 * width * i], sizeof(*bm->image) * 4, width, inFile);

			}

		}
	}

	// 7. Load the file if it is 24 bits
	// 7a. If the file is 24 bits, you need to read 3 bytes at a time and make space in memory for
	//     the extra byte. (Since your internal storage should always be 32 bits.)
	// 7b. If the height is negative, you need to read from disk into the rows in memory in reverse order
	// 7c. If the length of each line isn't divisible by 4, you need to read extra padding from the file.
	//     This padding shouldn't be stored in the bitmap data in memory.

	if (bitsPerPixel == 24) {
		fseek(inFile, fileHeader.bfOffBits, SEEK_SET);
		int length = 0;
		if (isReversed) { //Height is Negative
			for (int i = h - 1; i >= 0; i--) {
				if ((length % 4) != 0){
					uint32_t extraPadding;
					fread(&extraPadding, sizeof(4 - (length % 4)), 1, inFile);
				}
				for (int j = 0; j < width; j++) {
					length += fread(&bm->image[4 * (j + i * width)], sizeof(*bm->image), 3, inFile);
					bm->image[(4 * (j + i * width)) + 3] = 0;
				}
			}
		}
		else {
			for (int i = 0; i < h; i++) {
				if ((length % 4) != 0) {
					uint32_t extraPadding;
					fread(&extraPadding, sizeof(4 - (length % 4)), 1, inFile);
				}
				for (int j = 0; j < width; j++) {
					length += fread(&bm->image[4 * (j + i * width)], sizeof(*bm->image), 3, inFile);
					bm->image[(4 * (j + i * width)) + 3] = 0;
				}
			}

		}
	}
	
	// 8. Close the file.
	fclose(inFile);
	// 9. Return a pointer to the bitmap.
	return bm;
}

