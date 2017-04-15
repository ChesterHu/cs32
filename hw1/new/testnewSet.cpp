#include "newSet.h"
#include <iostream>
using namespace std;

void test0() {
	Set a(2);
	a.insert("hello");
	a.insert("hello");
	a.insert("world");
	a.insert("world");
	a.insert("insert");
	a.insert("insert");
	cout << a.size() << endl;
	a.dump();
}
