// ItemType unsigned long 
#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	do {
		SSNSet ss;
		assert(ss.size() == 0);
		assert(ss.add(11111111));
		assert(!ss.add(11111111));
		assert(ss.add(55555555));
		assert(!ss.add(55555555));
		assert(ss.add(11111110));
		assert(ss.add(33333333));
		assert(!ss.add(33333333));
		assert(ss.add(66666666));
		assert(ss.size() == 5); // Should be 5
		ss.print();
	} while(0);
}

int main() {
	test();
	cout << "Passed all tests" << endl;
}
