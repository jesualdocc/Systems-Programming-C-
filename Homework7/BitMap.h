/*
 *  BitMap.h
 *  HW 3
 */

#ifndef BITMAPPIC_H
#define BITMAPPIC_H

#include <cstdio>
#include <vector>
#include <cstdint>

struct BitMapHeader
{
	BitMapHeader()
	:zero(0), bfOffBits(sizeof(BitMapHeader)+2), biSize(40), biPlanes(1),
	biBitCount(32), biCompression(0), biSizeImage(0), biXPelsPerMeter(2835), biYPelsPerMeter(2835),
	biClrUsed(0), biClrImportant(0) {}
	
	uint32_t bfSize;
	uint32_t zero;
	uint32_t bfOffBits;
	
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};

class BitMap
{
public:
	BitMap(int w, int h);
	BitMap(const char* file);
	~BitMap();
	BitMap(const BitMap& b);
	BitMap& operator=(const BitMap& b);
	void Save(const char *file);
	BitMap* DetectEdges(int threadCount) const;
	void SetPixel(int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte );
	void GetPixel(int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte) const;
	void computeGS(int j, int i, uint8_t *greyScale) const; //Helper Function
	void threadedOp(int startH, int endH, int startW, int endW, BitMap *b) const;
private:
	uint32_t width, height;
	uint8_t *image;
};

typedef BitMap* BitMapPointer;

#endif
