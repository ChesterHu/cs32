#include "Set.h"
//#include <string>
#include <iostream>
#include <cassert>
using namespace std;

/*
void test()
{
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "bing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");

	cout << "Test passed" << endl;
}
*/

void test()
{
	Set uls;
	assert(uls.insert(20));
	assert(uls.insert(10));
	assert(uls.size() == 2);
	assert(uls.contains(10));
	ItemType x = 30;
	assert(uls.get(0, x) && x == 10);
	assert(uls.get(1, x) && x == 20);
	cout << "Test passed" << endl;
}

int main()
{
	test();

	return 0;
}
