#define _CRT_SECURE_NO_WARNINGS

#include "GroceryItem.h"
#include <iostream>


GroceryItem::GroceryItem(float p ,const char *d, float w):price(p), weight(w)
{
	description = new char[strlen(d) + 1];
	
	strcpy(description, d);
}


GroceryItem::~GroceryItem()
{
	delete[] description;
}

float GroceryItem::GetPrice() const
{
	return price;
}

char * GroceryItem::GetDescription() const
{
	return description;
}

float GroceryItem::GetWeight() const
{
	return weight;
}

void GroceryItem::setPrice(float p)
{
	price = p;
}


