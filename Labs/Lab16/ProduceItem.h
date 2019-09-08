#pragma once
#include "GroceryItem.h"
class ProduceItem :public GroceryItem
{
public:
	ProduceItem(float costPerPound, const char * d, float w);
	~ProduceItem();
	float GetCostPerPound() const;
private:
	float costPerPound;
};

