#include "ProduceItem.h"



ProduceItem::ProduceItem(float costPerPound, const char * d, float w):GroceryItem(0, d, w)
{
	this->costPerPound = costPerPound;
}


ProduceItem::~ProduceItem()
{
}

float ProduceItem::GetCostPerPound() const
{
	return costPerPound;
}
