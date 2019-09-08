/*
 *  BitMap.cpp
 *  HW 3
 */
#define _CRT_SECURE_NO_WARNINGS

#include "BitMap.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <thread>
#include "SharedQueue.h"
#include <mutex>


BitMap::BitMap(int w, int h):width(w), height(h)
{
  image = new uint8_t[width*height*4];
}

BitMap::BitMap(const char* file)
{
  bool loadFailed = false;
  FILE *f = fopen(file, "rb");
  BitMapHeader header;
  
  if (f == 0)
  {
    std::cout << "Unable to find file\n";
    loadFailed = true;
  }
  else
  {
    uint16_t bfType;
    fread(&bfType, sizeof(bfType), 1, f);
    if (bfType != 19778)
    {
      std::cout << "Unable to load file properly\n";
      fclose(f);
      loadFailed = true;
    }
    else
    {
      fread(&header, sizeof(BitMapHeader), 1, f);
      if (header.biBitCount < 24)
      {
        std::cout << "We only support 24 & 32-bit files\n";
        fclose(f);
        loadFailed = true;
      }
      else
      {
        std::cout << ":" << header.biBitCount << "bit image\n";
        
        if (header.biCompression != 0)
        {
          std::cout << "We don't support compressed files\n";
          fclose(f);
          loadFailed = true;
        }
        else
        {
          height = header.biHeight;
          bool reverseHeight = false;
          if ((int32_t)header.biHeight < 0)
          {
            std::cout << ":height reversed\n";
            height = (-1) * height;
            reverseHeight = true;
          }
          
          width = header.biWidth;
          image = new uint8_t[height*width*4];
          
          fseek(f, header.bfOffBits, SEEK_SET);
          
          if (header.biBitCount == 32)
          {
            for (int x = 0; x < height; x++)
            {
              if (reverseHeight)
                fread(&image[(height-x-1)*width*4], sizeof(char), width*4, f);
              else
                fread(&image[x*width*4], sizeof(char), width*4, f);
            }
          }
          else if (header.biBitCount == 24)
          {
            bool padding = false;
            for (int x = 0; x < height; x++)
            {
              int bytesRead = 0;
              for (int y = 0; y < width; y++)
              {
                if (reverseHeight)
                  bytesRead += fread(&image[(height-x-1)*width*4+y*4], sizeof(char), 3, f);
                else
                  bytesRead += fread(&image[x*width*4+y*4], sizeof(char), 3, f);
                image[x*width*4+y*4+3] = 0;
              }
              while (0 != bytesRead%4)
              {
                char zero[4] = {0, 0, 0, 0};
                bytesRead += fread(zero, sizeof(char), 1, f);
                padding = true;
              }
            }
            if (padding)
              std::cout << ":padding necessary\n";
          }
          fclose(f);
        }
      }
    }
  }
  
  if(loadFailed)
  {
    width = 10;
    height = 10;
    image = new uint8_t[width*height*4];
    for(int i=0; i < width*height*4; i++)
    {
      image[i] = 255;
    }
  }

  
}

BitMap::BitMap(const BitMap& b):width(b.width), height(b.height)
{
  image = new uint8_t[width*height*4];
  
  for(int i=0; i < width*height*4; i++)
  {
    image[i] = b.image[i];
  }
}

BitMap::~BitMap()
{
  width = 0;
  height = 0;
  if(image)
  {
    delete[] image;
    image = NULL;
  }
}

BitMap& BitMap::operator=(const BitMap& b)
{
  if(this == &b)
    return *this;
  
  width = b.width;
  height = b.height;
  
  delete[] image;
  image = new uint8_t[width*height*4];
  
  for(int i=0; i < width*height*4; i++)
  {
    image[i] = b.image[i];
  }
  
  return *this;
}

void BitMap::Save(const char *file)
{
  FILE *f = fopen(file, "w+");
  
  if (f == 0)
    return;
  
  BitMapHeader header;
  header.biWidth = width;
  header.biHeight = height;
  
  header.bfSize = sizeof(BitMapHeader)+2+(width)*height*4;
  header.biSizeImage = (width)*height*4;
  uint16_t bfType = 19778; // 0x4D42
  fwrite(&bfType, sizeof(bfType), 1, f);
  fwrite(&header, sizeof(header), 1, f);
  for (int x = 0; x < height; x++)
  {
    fwrite(&image[x*width*4], sizeof(char), width*4, f);
  }
  fclose(f);
}


void BitMap::SetPixel(int x, int y, uint8_t redByte, uint8_t greenByte, uint8_t blueByte, uint8_t alphaByte )
{
  // BGRA
  image[y*width*4+x*4+0] = blueByte;
  image[y*width*4+x*4+1] = greenByte;
  image[y*width*4+x*4+2] = redByte;
  image[y*width*4+x*4+3] = alphaByte;
}

void BitMap::GetPixel(int x, int y, uint8_t &redByte, uint8_t &greenByte, uint8_t &blueByte, uint8_t &alphaByte) const
{
  blueByte = image[y*width*4+x*4+0];
  greenByte = image[y*width*4+x*4+1];
  redByte = image[y*width*4+x*4+2];
  alphaByte = image[y*width*4+x*4+3];
}



BitMap* BitMap::DetectEdges(int threadCount) const
{
	BitMap *bm = new BitMap(this->width, this->height);

	bm->operator= (*this);

	SharedQueue<int> *workQueue = new SharedQueue<int>; //Queue of Rows

	int volatile *tmp = new int;

	for (int i = 1; i < bm->height - 1; i++) {
		workQueue->Add(i);
	}

	std::thread **threads = new std::thread*[threadCount];

	for (int i = 0; i < threadCount; i++) {
		threads[i] = new std::thread(&BitMap::threadedOp, this, bm, workQueue, tmp);
	}
	
	while (true) {
		if (*tmp >= height) {
			for (int i = 0; i < threadCount; i++) {
				threads[i]->join();
				delete threads[i];
			}

			delete[] threads;
			delete tmp;
			delete workQueue;
			break;
		}
	}


	return bm;
}

void BitMap::threadedOp(BitMap *b, SharedQueue<int> *q, int *count) const{

	while (true) {
		while (q->IsEmpty()) {
			std::this_thread::yield();
		}

		int row;

		q->Remove(row);

		for (int j = 1; j < b->width - 1; j++) { //Compute gray values for given row
			ComputeGS(j, row, b);
		}

		*count = (*count) + 1;
		
	}
}


void BitMap::ComputeGS(int j, int i, BitMap *b) const{ //Helper Function

			uint8_t R, G, B, A = 0;

			uint8_t greyScale[8] = { 0,0,0,0,0,0,0,0 };
	
			GetPixel(j - 1, i + 1, R, G, B, A);
			greyScale[0] = ((R + G + B) / 3); // [0] - Top Left
		
			GetPixel(j, i + 1, R, G, B, A);
			greyScale[1] = ((R + G + B) / 3); //[1] - Top Center
		
			GetPixel(j + 1, i + 1, R, G, B, A);
			greyScale[2] = ((R + G + B) / 3); //[2] - Top Right
		
			GetPixel(j - 1, i, R, G, B, A);
			greyScale[3] = ((R + G + B) / 3); // [3] - Left
		
			GetPixel(j + 1, i, R, G, B, A);
			greyScale[4] = ((R + G + B) / 3); // [4] - Right
		
			GetPixel(j - 1, i - 1, R, G, B, A);
			greyScale[5] = ((R + G + B) / 3); //[5] - Bottom Left
		
			GetPixel(j, i - 1, R, G, B, A);
			greyScale[6] = ((R + G + B) / 3); //[6] - Bottom Center
		
			GetPixel(j + 1, i - 1, R, G, B, A);
			greyScale[7] = ((R + G + B) / 3); //[7] - Bottom Right

			int VxTop = greyScale[0] * (-1) + greyScale[1] * (-2) + greyScale[2] * (-1);
			int VxBottom = greyScale[5] * (1) + greyScale[6] * (2) + greyScale[7] * (1);
			int Vx = VxTop + VxBottom;

			int VyLeft = greyScale[0] * (-1) + greyScale[3] * (-2) + greyScale[5] * (-1);
			int VyRight = greyScale[2] * (1) + greyScale[4] * (2) + greyScale[7] * (1);

			int Vy = VyLeft + VyRight;

			uint8_t gray = sqrt(Vx * Vx + Vy * Vy);

			b->SetPixel(j, i, (255 - gray), (255 - gray), (255 - gray), 0);
}


