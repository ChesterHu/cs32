// ItemType std::string
#include "Set.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	do {
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "bing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");
	} while(0);

	do {
		Set ss;
		assert(ss.insert("lavash"));
		assert(ss.insert("roti"));
		assert(ss.insert("chapati"));
		assert(ss.insert("injera"));
		assert(!ss.insert("roti"));
		assert(ss.insert("matzo"));
		assert(!ss.insert("injera"));
		assert(ss.size() == 5);
		ItemType x;
		assert(ss.get(0, x) && x == "chapati");
		assert(ss.get(4, x) && x == "roti");
		assert(ss.get(2, x) && x == "lavash");
	} while(0);

	do {
		Set ss;
		ss.insert("dosa");
		assert(!ss.contains(""));
		ss.insert("tortilla");
		ss.insert("");
		ss.insert("focaccia");
		assert(ss.contains(""));
		ss.erase("dosa");
		assert(ss.size() == 3 && ss.contains("focaccia") && ss.contains("tortilla") && ss.contains(""));
		ItemType v;
		assert(ss.get(1, v) && v == "focaccia");
		assert(ss.get(0, v) && v == "");
	} while(0);

	do {
		Set ss1;
		ss1.insert("bing");
		Set ss2;
		ss2.insert("matzo");
		ss2.insert("pita");
		ss1.swap(ss2);
		assert(ss1.size() == 2 && ss1.contains("matzo") && ss1.contains("pita") && ss2.size() == 1 && ss2.contains("bing"));
	} while(0);
}

int main()
{
	test();
	cout << "Paased all tests" << endl;
	return 0;
}
