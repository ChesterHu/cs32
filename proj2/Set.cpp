#include <iostream>  	// For test only
#include "Set.h"

	// Default constructor.
Set::Set()
{
	m_size = 0;
	m_head = new Node;
		// Initialize a circle.
	m_head->next = m_head;
	m_head->prev = m_head;
}

	// Copy constructor.
Set::Set(const Set& other)
{
	m_head = new Node;
	m_head->next = m_head;
	m_head->prev = m_head;

	m_size = 0;
	for (Node* iter = other.m_head->next; iter != other.m_head; iter = iter->next)
		this->insert(iter->data);	
}

	// Deconstructor
Set::~Set()
{
	while (m_size != 0)
	{
		Node* iter = m_head->next;
		m_head->next = iter->next;
		iter->next->prev = m_head;
		
		delete iter;
		m_size--;
	}

	delete m_head;
}

	// Assignment operator
Set& Set::operator=(const Set& rhs)
{
	if (this != &rhs)
	{
		Set temp(rhs);
		this->swap(temp);
	}
	return *this;
}

	// Return false if Set is empty.
bool Set::empty() const
{
	return (m_size == 0) ? true : false;
}

	// Return the size of Set.
int Set::size() const
{
	return m_size;
}

	// Return true if successfully insert a value into Set.
bool Set::insert(const ItemType& value)
{
	Node* iter = m_head->next;
	for (; iter != m_head && iter->data < value; iter = iter->next);
		
		// Need insertion
	if (iter == m_head || iter->data != value)
	{
			// Create new Node.
		Node* newGuy = new Node;
		newGuy->data = value;
		newGuy->next = iter;
		newGuy->prev = iter->prev;
			// Modify connection in list.
		iter->prev->next = newGuy;
		iter->prev = newGuy;
			// Update size.	
		m_size++;
		return true;
	}
	
	return false;	
}

	// Return true if successfully erase a value from Set.
bool Set::erase(const ItemType& value)
{
	Node* iter = m_head->next;
	for(; iter != m_head && iter->data < value; iter = iter->next);
		// Not in the list.
	if (iter == m_head || iter->data != value)
		return false;
		// In the list.
	iter->prev->next = iter->next;
	iter->next->prev = iter->prev;
		// Update size.
  delete iter;
	m_size--;
	return true;
}

	// Return true if the value is in the Set.
bool Set::contains(const ItemType& value) const
{
	Node* iter = m_head->next;
	for (; iter != m_head && iter->data != value; iter = iter->next);
		// If iter points to head, valu must not in list.
	return (iter != m_head) ? true : false;
}

	// Return true if pos in range of Set, and copy value in pos to value.
bool Set::get(int pos, ItemType& value) const
{
	if (pos < 0 || pos >= m_size)
		return false;

	Node* iter = m_head->next;
	for(; pos > 0; --pos, iter = iter->next);
	value = iter->data;

	return true;
}

	// Swap two Set.
void Set::swap(Set& other)
{
		// Swap size.
	int temp = other.m_size;
	other.m_size = m_size;
	m_size = temp;
		// Swap head pointer.
	Node* ptr = other.m_head;
	other.m_head = m_head;
	m_head = ptr;
}

	// Unite
void unite(const Set& s1, const Set& s2, Set& result)
{
	Set temp;
	ItemType x;
		// Insert s1 data.
	for (int i = 0; i < s1.size(); ++i)
	{
		s1.get(i, x);
		temp.insert(x);
	}
		// Erase d2 data.
	for (int i = 0; i < s2.size(); ++i)
	{
		s2.get(i, x);
		temp.insert(x);
	}
		// Swap items.
	result.swap(temp);
}

	// Subtract
void subtract(const Set& s1, const Set& s2, Set& result)
{
	Set temp;
	ItemType x;
		// Insert s1 data.
	for (int i = 0; i < s1.size(); ++i)
	{
		s1.get(i, x);
		temp.insert(x);
	}
		// Erase s2 data.
	for (int i = 0; i < s2.size(); ++i)
	{
		s2.get(i, x);
		temp.erase(x);
	}

	result.swap(temp);
}

	// Test func
void Set::dump() const
{
	for(Node* iter = m_head->next; iter != m_head; iter = iter->next)
		std::cout << iter->data << std::endl;
}
