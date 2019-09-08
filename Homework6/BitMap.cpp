#define _CRT_SECURE_NO_WARNINGS

#include "BitMap.h"
#include <iostream>

BitMap::BitMap()
{
	width = 0;
	height = 0;
	image = NULL;
	fileHeader = new BitMapHeader;
	
}

BitMap::BitMap(int w, int h)
{
	fileHeader = new BitMapHeader;
	CreateBitMapPic(w, h);
	
}

BitMap::BitMap(const BitMap & bm)
{
	width = bm.width;
	height = bm.height;

	fileHeader = new BitMapHeader;
	*fileHeader = *(bm.fileHeader);
	image = new uint8_t[bm.width * bm.height * 4];

	int size = bm.width * bm.height * 4;
	for (int i = 0; i < size; i++) {
		image[i] = bm.image[i];
	}
	
}

BitMap & BitMap::operator=(const BitMap & bm)
{
	if (this != &bm) {
		delete[] image; //Delete old Image
		delete fileHeader; //Delete old Header

		width = bm.width;
		height = bm.height;

		fileHeader = new BitMapHeader;
		*fileHeader = *(bm.fileHeader);

		image = new uint8_t[bm.width * bm.height * 4];
		
		int size = bm.width * bm.height * 4;
		for (int i = 0; i < size; i++) {
			image[i] = bm.image[i];
		}
	
	}
	return *this;
}

BitMap::~BitMap()
{
	if ((height != 0) || (width != 0) || (image != NULL)) {
		delete[] image;
		delete fileHeader;
	}
}

bool BitMap::CreateBitMapPic(int w, int h)
{
	
	if ((height != 0) || (width != 0) || (image != NULL)) {
		std::cout << "Object is An Image Already\n";
		return false;
	}

	height = h;
	width = w;

	fileHeader->biHeight = h;
	fileHeader->biWidth = w;

	image = new uint8_t[w * abs(h) * 4]; 

	return true;
}

void BitMap::Load(const char * file)
{
	// 0. If any of the operations fail, free any memory and return 0

	// 1. Open the file

	FILE *inFile = fopen(file, "rb+");

	if (inFile == NULL) {
		std::cout << "Error!! File Not Found\n";
		delete inFile;
		return ;
	}

	// 2a. Read the initial fields of the header; verify that the file type (BM) is correct.

	uint16_t *signatureField = new uint16_t;

	fread(signatureField, 2, 1, inFile);

	if (!(*signatureField == 19778)) {
		std::cout << "Error!! Not .bmp File\n";
	}

	delete signatureField;

	// 2b. Read the rest of the header.

	if ((height != 0) || (width != 0) || (image != NULL)) { //Delete Old Picture if object loading has one  - Allocate memory for new one

		delete [] image;
		delete fileHeader;
		image = NULL;
		width = 0;
		height = 0;
		fileHeader = new BitMapHeader;
		
	}

	fread(fileHeader, sizeof(fileHeader), 1, inFile);


	CreateBitMapPic(fileHeader->biWidth, fileHeader->biHeight);


	// 3. Verify if the file is 24 or 32 bits.
	uint32_t bitsPerPixel = fileHeader->biBitCount;

	// 4. Check if the rows are stored in reverse order (due to negative height)

	int h = (int32_t)fileHeader->biHeight;

	bool isReversed = h < 0;

	// 5. Make sure the file isn't compressed (compression should be 0)

	bool isCompressed = fileHeader->biCompression;

	if (isCompressed) {
		return ;
	}

	h = abs(h);

	// 6. Load the file if it is 32 bits
	// 6a. If the file is 32 bits, you can read one row at a time.
	// 6b. If the height is negative, you need to read from disk into the rows in memory in reverse order
	// 6c. 32-bit files are never padded.

	if (bitsPerPixel == 32) {
		fseek(inFile, fileHeader->bfOffBits, SEEK_SET);
		if (isReversed) {
			for (int i = h - 1; i >= 0; i--) {
				//Start Filling from the top row, (width * 4) bytes for each row
				fread(&image[4 * width * i], width * 4, 1, inFile);
			}
		}
		else {
			for (int i = 0; i < h; i++) {
				//Start Filling from the bottom row, (width * 4) bytes for each row

				fread(&image[4 * width * i], width * 4, 1, inFile);

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
		fseek(inFile, fileHeader->bfOffBits, SEEK_SET);
		int length = 0;
		if (isReversed) { //Height is Negative
			for (int i = h - 1; i >= 0; i--) {
				if ((length % 4) != 0) {
					uint32_t extraPadding;
					fread(&extraPadding, sizeof(4 - (length % 4)), 1, inFile);
				}
				for (int j = 0; j < (int) width; j++) {
					length += fread(&image[4 * (j + i * width)], sizeof(*image), 3, inFile);
					image[(4 * (j + i * width)) + 3] = 0;
				}
			}
		}
		else {
			for (int i = 0; i < h; i++) {
				if ((length % 4) != 0) {
					uint32_t extraPadding;
					fread(&extraPadding, sizeof(4 - (length % 4)), 1, inFile);
				}
				for (int j = 0; j < (int) width; j++) {
					length += fread(&image[4 * (j + i * width)], sizeof(*image), 3, inFile);
					image[(4 * (j + i * width)) + 3] = 0;
				}
			}

		}
	}

	// 8. Close the file.
	fclose(inFile);

}

bool BitMap::Save(const char * file)
{
	if ((height == 0) || (width == 0) || (image == NULL) || (fileHeader == NULL)) {

		std::cout << "No Data Available to Save\n";
		return false;
	}
	// 1. Open the file

	FILE * outFile;
	outFile = fopen(file, "wb+");

	// 2. Create a header and write it to the file

	uint16_t signatureField = 19778;

	int returnValue = fwrite(&signatureField, sizeof(signatureField), 1, outFile);

	if (returnValue != 1) { // 1 is count value
		std::cout << "Error Writing File!! \n";
	}

	fwrite(fileHeader, sizeof(*fileHeader), 1, outFile);

	

	int count = height * width * 4;
	// 3. Write the bitmap data to the file

	returnValue = fwrite(image, sizeof(*image), count, outFile);

	if (returnValue != count) { // 1 is count value
		std::cout << "Error Writing File!! \n";
		return false;
	}

	// 4. Close the file
	fclose(outFile);
	return true;
}

void BitMap::GetPixel(int x, int y, uint8_t & redByte, uint8_t & greenByte, uint8_t & blueByte, uint8_t & alphaByte)
{
	//B-G-R-A (Order from instructions)
	blueByte = image[4 * (x + y * width)]; //[0]
	greenByte = image[4 * (x + y * width) + 1]; //[1]
	redByte = image[4 * (x + y * width) + 2]; //[2]
	alphaByte = image[4 * (x + y * width) + 3];//[3]
}

void BitMap::SetPixel(int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte)
{
	
//B-G-R-A (Order from instructions)

	image[(4 * (x + y * width))] = blueByte; //[0]
	image[(4 * (x + y * width)) + 1] = greenByte; //[1]
	image[(4 * (x + y * width)) + 2] = redByte; //[2]
	image[(4 * (x + y * width)) + 3] = alphaByte; //[3]
}
