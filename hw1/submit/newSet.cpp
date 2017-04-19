#include "newSet.h"
#include <string>   // ItemType can be std::string
#include <iostream> // Using cerr

Set::Set(int cap)
{
	if (cap <= 0) {
		std::cerr << "Capacity must be greater than 0\n";
	}
	m_size = 0;
	m_cap = cap;
	m_items = new ItemType[m_cap];
}

Set::Set(const Set& other)
{
	m_size = other.m_size;
	m_cap = other.m_cap;
	m_items = new ItemType[m_cap];
	
	// Copy items
	for (int i = 0; i < m_size; ++i)
		m_items[i] = other.m_items[i];
}

Set& Set::operator=(const Set& rhs)
{
	if (this != &rhs) {
		Set temp(rhs);
		this->swap(temp);
		/*
		delete [] m_items;
		m_size = rhs.m_size;
		m_cap = rhs.m_cap;
		m_items = new ItemType[m_cap];

		for (int i = 0; i < m_size; ++i)
			m_items[i] = rhs.m_items[i];
		*/
	}
	
	return *this;
}

Set::~Set()
{
	delete [] m_items;
}

bool Set::empty() const
{
	return (m_size == 0) ? true : false;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
		// If the set is already full.
	if (m_size >= m_cap)
		return false;
		// If the set is empty.
	if (m_size == 0 && m_cap > 0) {
		m_items[0] = value;
		m_size++;
		return true;
	}

		// Find a place to insert.
	int left = 0, right = m_size - 1, mid = 0;
	
	while (left <= right) {
		mid = (left + right) / 2;
		if (m_items[mid] == value) {
			return false;
		} else if (m_items[mid] < value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

		// "idx" is the place to insert.
	int idx = (m_items[mid] > value) ? mid : mid + 1;
		// Move every item to right 1 block, start from idx.
	for (int i = m_size - 1; i >= idx; --i)
		m_items[i + 1] = m_items[i];
		// Insert
	m_items[idx] = value;
	m_size++;

	return true;
}

bool Set::erase(const ItemType& value)
{
		// If set is empty.
	if (m_size == 0) 
		return false;

		// Find the item.
	int left = 0, right = m_size - 1, mid = 0;
	bool in = false;

	while (left <= right) {
		mid = (left + right) / 2;
		if (m_items[mid] == value) {
			in = true;
			break;	
		} else if (m_items[mid] < value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

		// If value not in.
	if (!in)
		return false;

		// move every item to left 1 block.
	for (int i = mid + 1; i < m_size; ++i) {
		m_items[i - 1] = m_items[i];
	}
	m_size--;
	
	return true;
}

bool Set::contains(const ItemType& value) const
{
		// If set is empty, return false.
	if (m_size == 0)
		return false;

		// Find the item.
	int left = 0, right = m_size - 1;
	
	while (left <= right) {
		int mid = (left + right) / 2;
		if (m_items[mid] == value) {
			return true;
		} else if (m_items[mid] < value) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}

	return false;
}

bool Set::get(int i, ItemType& value) const
{
	if (i >= 0 && i < m_size) {
		value = m_items[i];
		return true;
	}
	return false;
}

void Set::swap(Set& other)
{
		// Switch size.
	int temp = other.m_size;
	other.m_size = this->m_size; 
	this->m_size = temp;

		// Switch max capacity.
	temp = other.m_cap;
	other.m_cap = this->m_cap; 
	this->m_cap = temp;

		// Switch pointer.
	ItemType* ptr = other.m_items;
	other.m_items = this->m_items;
	this->m_items = ptr;
}
