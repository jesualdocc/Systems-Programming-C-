#include "Lettuce.h"



Lettuce::Lettuce(float w):ProduceItem(0.49, "Lettuce",w )
{
	setPrice(GetWeight() * GetCostPerPound());
}


Lettuce::~Lettuce()
{
}
