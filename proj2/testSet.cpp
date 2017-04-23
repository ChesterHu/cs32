#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	// default constructor
	Set s;
	// For an empty set:
	assert(s.empty());     // test empty;
	assert(s.size() == 0);		// test size;
	assert(!s.erase("Hua"));	// nothing to remove
	assert(!s.contains("Hua"));	// nothing contained
	// Start to add something into an empty set
	assert(s.insert("Nan"));	// test insert, insert "Nan" successfully
	assert(s.erase("Nan"));		// test erase, erase "Nan" successfully
	assert(s.empty());			// test empty again
	// Start to add something into an empty set
	assert(s.insert("Nan"));	// test insert, insert "Nan" successfully
	assert(s.insert("Hua"));	// test insert, insert "Hua" successfully
	assert(s.erase("Hua"));		// test erase, erase "Hua" successfully
	assert(s.insert("Hua"));	// test insert, insert "Hua" successfully
	assert(s.insert("Mingyue"));	// test insert, insert "Mingyue" successfully
	assert(s.contains("Hua"));	// test contains, contains "Hua"
	assert(!s.contains("Chufeng"));  // test contains, do not have "Chufeng" in the set
	assert(s.size() == 3);		// test size; size should be 3 as there are "Hua", "Nan", and "Mingyue" in the set
	assert(s.erase("Mingyue"));	 // test erase, erase "Mingyue" successfully
	ItemType value;		// declare the value variable
	assert(s.get(1,value));		//test get, 0<=1<=s.size()= 2, should return true and return a value to "value"
	assert(value == "Nan");		// the value which is exactly greater than 1 item in the set should be "Nan" (Hua, Nan)
	assert(!s.get(2,value)); 	// test get when i is greater or equal to size, should return false;
	// copy constructor
	Set t(s); 	// test copy constructor
	assert(t.size() == 2);   // test the copy constructor, size of t should be the same as size of s, which equals to 2
	assert(t.insert("Chenyang"));	// test insert to the copy set.
	// assign operator
	s = t;		// test assign operator
	assert(s.size() == 3);	// test the size of assigned set s.
	// give a new set b
	Set b;
	assert(b.insert("Rita"));
	assert(b.insert("Kathy"));
	assert(b.insert("Hua"));
	// give a new set c
	Set c;
	// unite function
	unite(s, b, c);	// test unite function
	c.dump();	// result should be "Chenyang","Hua","Kathy","Nan","Rita"
	cout << "=========" << endl;
	unite(s,s,s); // check aliasing
	s.dump();	// result should be "Chenyang", "Hua", "Nan"
	cout << "=========" << endl;
	// subtract function
	subtract(s, b, c);	//test subtract function
	c.dump();	// result should be "Chenyang", "Nan"
}