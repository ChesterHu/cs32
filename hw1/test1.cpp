// ItemType unsigned long
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	do{
	Set uls;
	assert(uls.insert(20));
	assert(uls.insert(10));
	assert(uls.size() == 2);
	assert(uls.contains(10));
	ItemType x = 30;
	assert(uls.get(0, x) && x == 10);
	assert(uls.get(1, x) && x == 20);
	} while(0);

	do{
	Set s;
	assert(s.empty());
	ItemType x = 9876543;
	assert(!s.get(42, x) && x == 9876543);
	s.insert(123456789);
	assert(s.get(0, x) && x == 123456789);
	} while(0);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
	return 0;
}
