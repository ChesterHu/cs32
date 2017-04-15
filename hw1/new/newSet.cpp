#include "newSet.h"
#include <string>
Set::Set()
{
	m_size = 0;
	m_maxItems = DEFAULT_MAX_ITEMS;
	m_items = new ItemType[m_maxItems];
}

Set::Set(int num_items)
{
	m_size = 0;
	m_maxItems = num_items;
	m_items = new ItemType[num_items];
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
	if (m_size >= m_maxItems)
		return false;
	// If the set is empty.
	if (m_size == 0 && m_maxItems > 0) {
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
	int max_size = (this->size() > other.size()) ? this->size() : other.size();

	for (int i = 0; i < max_size; ++i) {
		ItemType temp = other.m_items[i];
		other.m_items[i] = this->m_items[i];
		this->m_items[i] = temp;
	}

	int temp_size = other.m_size;
	other.m_size = this->m_size;
	this->m_size = temp_size;
}
