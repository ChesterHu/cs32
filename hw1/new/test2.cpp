// ItemType unsigned long
#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set a(1000);
	Set b(5);
	Set c;
	const ItemType v[6] = {1, 6, 5, 2, 3, 4};

	assert(a.size() == 0 && b.size() == 0 && c.size() == 0);
	for (int i = 0; i < 5; ++i)
		assert(b.insert(v[i]));
	assert(!b.insert(v[5]));
		// Copy constructor.
	for (int i = 0; i < 10; ++i) {
		Set e(b);
		assert(e.size() == 5);
		assert(!e.insert(1));
		ItemType x;
		assert(e.get(0, x) && x == 1);
		assert(!e.get(5, x));
		assert(e.get(4, x) && x == 6);
	}
		// Assignment operator.
	do {
		Set d, e;
		e = d = b = b;
		assert(e.size() == 5);
		assert(!e.insert(1));
		assert(!e.insert(6));
		assert(!e.insert(100));
		ItemType x;
		assert(e.get(0, x) && x == 1);
		assert(!e.get(5, x));
		assert(e.get(4, x) && x == 6);
	} while(0);

		// Swap
	a.swap(b);
  a.swap(a);
	assert(a.size() == 5 && b.size() == 0);
	ItemType x;
	assert(a.get(0, x) && x == 1);
	assert(!a.get(5, x));
	assert(a.get(4, x) && x == 6);
	assert(!a.insert(100) && b.insert(100));
	assert(b.get(0, x) && x == 100);
}

int main() 
{
	test();
	cout << "Passed all tests" << endl;
}
