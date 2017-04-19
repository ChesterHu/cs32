#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	SSNSet ss;
	ss.add(11111111);
	ss.add(11111111);
	ss.add(55555555);
	ss.add(55555555);
	ss.add(11111110);
	ss.add(33333333);
	ss.add(33333333);
	assert(ss.size() == 4);
	ss.print();
}

int main() {
	test();
	cout << "Passed all tests" << endl;
}
