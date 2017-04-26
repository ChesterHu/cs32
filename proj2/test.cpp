#include <iostream>
#include <cassert>
#include "Set.h"
using namespace std;

void test()
{
	do {
		Set a;
		assert(a.empty());
			// Insert
		assert(a.size() == 0);
		assert(a.insert("a"));
		assert(a.insert("b"));
		assert(a.insert("c"));
		assert(!a.insert("a"));
		assert(!a.insert("b"));
		assert(!a.insert("c"));
		assert(a.size() == 3 && !a.empty());
			// Contains
		assert(a.contains("a") && a.contains("b") && a.contains("c"));
		assert(!a.contains("d"));
			// Get
		ItemType x;
		assert(a.get(0, x) && x == "a");
		assert(a.get(1, x) && x == "b");
		assert(a.get(2, x) && x == "c");
			// Swap
		Set b;
		b.swap(a);
		assert(a.size() == 0 && a.empty() && b.size() == 3 && !b.empty());
			// Copy
		Set c(b);
		assert(c.get(0, x) && x == "a");
		assert(c.get(1, x) && x == "b");
		assert(c.get(2, x) && x == "c");
			// Assignment operator
		Set d, e;
		e = d = c = b = b = b;
		assert(e.get(0, x) && x == "a");
		assert(e.get(1, x) && x == "b");
		assert(e.get(2, x) && x == "c");
		assert(e.size() == 3);
	} while (0);

	do {
		Set a, b;
		assert(a.insert("a"));
		assert(a.insert("b"));
		assert(a.insert("c"));
		assert(a.insert("d"));
		assert(b.insert("c"));
		assert(b.insert("d"));
		assert(b.insert("e"));
		assert(b.insert("f"));
		assert(b.insert("g"));
		Set c;
		unite(a, b, c);
		cout << "unite" << endl;
		c.dump();
		assert(c.size() == 7);
		subtract(a, b, c);
		cout << "subtract" << endl;
		c.dump();
		assert(c.size() == 2);
	} while(0);

  do {
    Set a;
    a.insert("a");
    a.insert("b");
    a.insert("c");
    assert(a.erase("b"));
    assert(a.erase("c"));
    assert(a.erase("a"));
    assert(a.size() == 0);
    assert(!a.contains("a") && !a.contains("c") && !a.contains("b"));
  } while(0);
}

int main()
{
	test();
	cout << "Passed all test" << endl;

	return 0;
}
