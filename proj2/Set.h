#ifndef SET_INCLUDED
#define SET_INCLUDED
<<<<<<< HEAD
#include <string> // Using ItemType of std::string
=======

#include <string>		// For std::string ItemType
>>>>>>> af3e8628fc4a92d148e1367126635ddf135a6f6f
typedef std::string ItemType;

	// Implementation of double linked lisk (circular).
class Set
{
	public:
		Set();
		Set(const Set& other);
		~Set();
		Set& operator=(const Set& rhs);

			// APIs
		bool empty() const;
		int  size() const;
		bool insert(const ItemType& value);
		bool erase(const ItemType& value);
		bool contains(const ItemType& value) const;
		bool get(int pos, ItemType& value) const;
		void swap(Set& other);

			// For test only
		void dump() const;
	private:
			// Node
		struct Node
		{
			ItemType data;
			Node* prev;
			Node* next;
		};

		Node* m_head;
		int  	m_size;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // Set included
