#include "Celery.h"



Celery::Celery(float w) :ProduceItem(0.79, "Celery", w)
{
	setPrice (GetWeight() * GetCostPerPound());
}


Celery::~Celery()
{
}
