#include <iostream>
#include "BitMap.h"

int main() {

	//Test #1 - Creating a new picture, Saving it, copying it

	BitMap bm;
	bm.CreateBitMapPic(255, 255);

	for (int x = 0; x < 255; x++)
	{
		for (int y = 0; y < 255; y++)
		{
			bm.SetPixel(x, y, 255 - y, 255, y, 255);
		}
	}
	std::cout << "Processing Test1.bmp\n";
	bm.Save("Test1 - Default Constructor.bmp");

	BitMap bm2 = bm;
	std::cout << "Processing Test1 - Copy Constructor.bmp\n";
	bm2.Save("Test1 - Copy Constructor.bmp");
	BitMap bm3;
	bm3 = bm;
	std::cout << "Processing Test1 - Assignment Operator.bmp\n";
	bm3.Save("Test1 - Assignment Operator.bmp");

/*
	//Test #2 - Loading ,saving and copying and copying
	BitMap bm;
	bm.Load("train.bmp");
	bm.Save("Train Pic - Loaded and Saved.bmp");
	
*/
	return 0;
}