#include "Set.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

class Coord
{
	public:
		Coord(int r, int c) : m_r(r), m_c(c) {}
		Coord() : m_r(0), m_c(0) {}
		double r() const { return m_r; }
		double c() const { return m_c; }
	private:
		double m_r;
		double m_c;
};

void test()
{
	do {
		Set<int> a;
		a.insert(1);
		a.erase(1);
		Set<string> b;
		b.insert("a");
		b.erase("a");
		Set<double> c;
		c.insert(1.2);
		c.erase(1.2);
	} while (0);

	do {
		Set<int> a;
		Set<int> b;
		Set<int> c;
		for (int i = 0; i < 10; ++i)
			a.insert(i);
		for (int i = 5; i < 10; ++i)
			b.insert(i);
		unite(a, b, c);
		assert(c.size() == 10);
		subtract(a, b, c);
		assert(c.size() == 5);
	} while (0);
}

int main()
{
	test();
	Set<Coord> sc;
	sc.insert(Coord(4, -4));	// error!
	cout << "Passed all test" << endl;
}

