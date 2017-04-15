#include "SSNSet.h"
#include <iostream>
using namespace std;

void testSSN1()
{
	SSNSet ss;
	ss.add(11111111);
	ss.add(11111111);
	ss.add(55555555);
	ss.add(55555555);
	ss.add(11111110);
	ss.add(33333333);
	ss.add(33333333);
	cout << ss.size() << endl; // Should be 4
	ss.print();
}
