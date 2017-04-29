#include "Set.h"
#include "Set.h"
#include <cassert>
#include <iostream>
using namespace std;

void test() {
  do {
    Set a;
    assert(a.empty()); // For an empty set.
    // Insert
    assert(a.size() == 0);
    assert(a.insert("b"));
    assert(a.insert("a"));
    assert(a.insert("c"));
    assert(!a.insert("a"));
    assert(!a.insert("b"));
    assert(!a.insert("c"));  // For insert duplicate item.
    assert(a.size() == 3 && !a.empty());  // For size after insert.
    // Contains
    assert(a.contains("a") && a.contains("b") && a.contains("c"));
    assert(!a.contains("d")); // For contains().
    // Get
    ItemType x;
    assert(a.get(0, x) && x == "a");
    assert(a.get(1, x) && x == "b");
    assert(a.get(2, x) && x == "c"); // For get().
    // Swap
    Set b;
    b.swap(a);
    assert(a.size() == 0 && a.empty() && b.size() == 3 && !b.empty());  // For swap().
    // Copy
    Set c(b);
    assert(c.get(0, x) && x == "a");
    assert(c.get(1, x) && x == "b");
    assert(c.get(2, x) && x == "c");  // For copy().
    // Assignment operator
    Set d, e;
    e = d = c = b = b = b;
    assert(e.get(0, x) && x == "a");
    assert(e.get(1, x) && x == "b");
    assert(e.get(2, x) && x == "c");
    assert(e.size() == 3);						// For assignment operator.
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
    assert(b.insert("g")); 		// For insert.
    Set c;
    unite(a, b, c);						// For unite.
    assert(c.size() == 7);
    subtract(b, a, c);
    assert(c.size() == 3);	   // For subtract.
		assert(!c.erase("c"));
		assert(!c.erase("b"));
		assert(c.erase("e") && c.size() == 2); // For erase at head.
		ItemType x;
		assert(c.get(0, x) && x == "f");
		assert(c.get(1, x) && x == "g");
		assert(!c.get(2, x) && !c.get(-1, x) && x == "g");
		c.insert("e");
		assert(c.erase("f") && !c.contains("f")); // For erase at mid.
		assert(c.erase("g") && !c.contains("g")); // For erase at end.
		assert(c.size() == 1);
  } while (0);

  do {
    Set a, b, c;
    a.insert("abc");
    a.insert("bcd");
		a.insert("cde");
    a.insert("abc");
    unite(a, b, c);
    subtract(b, a, c);
		unite(a, a, a);
		subtract(a, a, a); // For aliasing.
		assert(a.size() == 0);
  } while (0);
  
	do {
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "bing";
    assert(ss.get(0, x) && x == "pita");
    assert(ss.get(1, x) && x == "roti");
  } while (0);

	do {
		Set a;
		a.insert("c");
		a.insert("d");
		a.insert("a");
		a.insert("b");
		a.erase("a");  // erase head item.
		ItemType x;
		assert(a.get(0, x) && x == "b");
		assert(a.get(1, x) && x == "c");
		assert(a.get(2, x) && x == "d");
		a.insert("a");
		a.erase("d");  // erase tail item.
		assert(a.get(0, x) && x == "a");
		assert(a.get(1, x) && x == "b");
		assert(a.get(2, x) && x == "c");
		a.insert("d");
		a.erase("c");  // erase middle item.
		assert(a.get(0, x) && x == "a");
		assert(a.get(1, x) && x == "b");
		assert(a.get(2, x) && x == "d");
	} while (0);
}

int main() {
  test();
  cout << "Passed all test" << endl;

  return 0;
}
