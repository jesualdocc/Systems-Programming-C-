#include <iostream>
#include "GroceryCart.h"

// These are sample items. Create your own
// unique items for your shopping cart!
#include "Celery.h"
#include "Lettuce.h"
#include "ChickenSoup.h"
#include "Banana.h"

int main(int argc, const char * argv[])
{
	GroceryCart c;
	c.AddItemToCart(new Lettuce(1.2)); // Weight in lbs (Lettuce is $0.49/lb)
	c.AddItemToCart(new Celery(1.5));  // Weight in lbs (Celery is $0.79/lb)
	c.AddItemToCart(new ChickenSoup);
	c.AddItemToCart(new Banana(2.0));
	std::cout << c;
	return 0;
}