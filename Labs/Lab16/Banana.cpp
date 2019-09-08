#include "Banana.h"


Banana::Banana(float w) :ProduceItem(0.25, "Banana", w)
{
	setPrice(GetWeight() * GetCostPerPound());
}


Banana::~Banana()
{
}
