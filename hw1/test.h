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
