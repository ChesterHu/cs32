#include <iostream>
#include "Set.h"

using namespace std;

void test0() {
  Set m_set;
	m_set.insert(1);
  m_set.insert(5);
	m_set.dump();
	cout << "Insert 5 again: "<< m_set.insert(5) << endl;
	m_set.insert(3);
 	m_set.insert(3);
	m_set.insert(2);
	m_set.insert(4);
	m_set.dump();
	cout << "size is " << m_set.size() << endl;
	cout << "start to erase item" << endl;
	m_set.erase(1);
	m_set.erase(1);
	m_set.erase(3);
	m_set.erase(3);
	m_set.erase(5);
	m_set.erase(5);
	m_set.dump();
}

void test1() {
	Set m_set;
	m_set.insert(1);
	m_set.insert(5);
	m_set.dump();
}

void test2() {
	Set m_set;
	
	for (int i = 0; i < 5; ++i)
		m_set.insert(i);

	for (int i = 0; i < 5; ++i)
		cout << m_set.contains(i) << endl;

}

void test3() {
	Set a;
	Set b;

	for (int i = 1; i <= 10; ++i)
		a.insert(i);

	for (int i = 11; i <= 40; ++i)
		b.insert(i);

	a.swap(b);
	cout << "a's items" << endl;
	a.dump();
	cout << "b's items" << endl;
	b.dump();
}
