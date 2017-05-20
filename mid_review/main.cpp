#include <iostream>
#include <cassert>
#include "car.h"
#include "picture.h"
using namespace std;

void test(Car& c)
{
	c.cruiseControl();
}

int main()
{
	GasTank g(10);
	Battery b;
	Car c(10);
	HybridCar h(3);
	assert(c.drive(110) == 100);
	test(h);
	assert(h.gallonsLeft() == 8);

	Picture p(10);
	for (int i = 0; i < 10; ++i)
		p.addCircle(i, i + 1, i + 2);
	p.printPicture();
	Picture p2(p);
	p2.printPicture();
	cout << "Passed all tests" << endl;
}
