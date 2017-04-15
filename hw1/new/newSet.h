#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
typedef unsigned long ItemType;  // Define ItemType as the synonym for desired data type.
const int DEFAULT_MAX_ITEMS = 200;

// include for testing dump;
#include <iostream>
using namespace std;

class Set 
{
	public:
		Set();
			// Default constructor, create an empty set.

		Set(int num_items);
			// Constructor, init with num_items blocks.

		Set(const Set& other);
			// Copy constructor.

		Set& operator=(const Set& rhs);
			// Assignment operater overloading.

		~Set();
			// Deconstructor.

		bool empty() const;
			// Return true if the set is empty, otherwise false.

		int size() const;
			// Return the number of items in the set.

		bool insert(const ItemType& value);
			// Insert value into the set if it is not already present.  Return
		  // true if the value was actually inserted.  Leave the set unchanged
		 	// and return false if the value was not inserted (perhaps because it
		  // is already in the set or because the set has a fixed capacity and
		  // is full).

		bool erase(const ItemType& value);
		  // Remove the value from the set if present.  Return true if the
		  // value was removed; otherwise, leave the set unchanged and
		  // return false.

    bool contains(const ItemType& value) const;
		  // Return true if the value is in the set, otherwise false.

    bool get(int i, ItemType& value) const;
		  // If 0 <= i < size(), copy into value the item in the set that is
		  // greater than exactly i items in the set and return true.  Otherwise,
		  // leave value unchanged and return false.
    
		void swap(Set& other);
		  // Exchange the contents of this set with the other one.

		void dump()
		{
		/*	
			for (int i = 0; i < m_size; ++i) {
				cout << m_items[i] << endl;
			}
		*/		
		}

	private:
		int				m_size;		// Current size.
		int				m_cap;		// Max capacity.
		ItemType* m_items;	// Current items.
};

#endif	// Set.h included
