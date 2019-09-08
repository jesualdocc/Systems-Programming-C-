#pragma once

#include <iostream>

class GroceryItem
{
public:
	GroceryItem(float p, const char *d , float w);
	~GroceryItem();
	float GetPrice() const;
	char *GetDescription() const;
	float GetWeight() const;
	void setPrice(float p);
	
	
private:
	float price;
	char *description;
	float weight;
};

