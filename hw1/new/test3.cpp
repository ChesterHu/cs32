// ItemType std::string
#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>	// Use assert for testing.
using namespace std;

void test0() 
{
	Set a(2);
	a.insert("hello");
	a.insert("hello");
	a.insert("world");
	a.insert("world");
	a.insert("insert");
	a.insert("insert");
	// cout << a.size() << endl;
	Set b(a);
	// cout << b.size() << endl;
	Set c(10);
	a = a;
	c = b = a;
	ItemType x = "";
	assert(c.get(0, x) && x == "hello");
	assert(c.size() == 2);
	// cout << c.size() << endl;
}

void test1() 
{
	Set a(1000);
	Set b(5);
	ItemType v[6] = {"abc", "bcd", "cde", "cbd", "bda", "dab"};
	
	for (int k = 0; k < 5; ++k)
		assert(b.insert(v[k]));

		// Falure to insert excess item
	assert(!b.insert(v[5]));

		// When swap two Sets, their contents are swapped, their capacities are swapped as well.
 	a.insert("hello");
	a.insert("world");
	a.swap(b);
	assert(!a.insert(v[5])  &&  b.insert(v[5]));
}

int main()
{
	test0();
	test1();
	cout << "Passed all tests" << endl;
}
