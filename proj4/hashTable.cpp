#include <string>
#include <cassert>
#include <iostream>
using namespace std;

const int TABLE_SIZE = 1000;
  // a hashTable for string
class hashTable
{
	public:
		hashTable();
		~hashTable();

		bool declare(string id, int lineNum);
		int find(string id) const;
	private:
		struct Node
		{
			string id;
			int lineNum;
			Node* next;
			Node(string new_id, int new_line) : id(new_id), lineNum(new_line), next(nullptr) {}
			~Node() { delete next; }
		};

		Node* bucket[TABLE_SIZE];
};

// function implementation
///////////////////////////////////////////////////////////

  // constructor
hashTable::hashTable()
{
	for (int i = 0; i < TABLE_SIZE; ++i)
		bucket[i] = nullptr;
}

  // destructor
hashTable::~hashTable()
{
	for (int i = 0; i < TABLE_SIZE; ++i)
		delete bucket[i];
}

  // return the hash value of a key
inline int hashF(const string& key)
{
	int hashVal = 0;
	for (int i = 0; i < key.size(); ++i)
		hashVal ^= key[i];
	return hashVal % TABLE_SIZE;
}

bool hashTable::declare(string id, int lineNum)
{
	Node** ptr = &bucket[hashF(id)];
	while (*ptr != nullptr)
	{
		if ((*ptr)->id == id) return false;
		ptr = &((*ptr)->next);
	}
	*ptr = new Node(id, lineNum);
	return true;
}

int hashTable::find(string id) const
{
	Node* ptr = bucket[hashF(id)];
	while (ptr != nullptr)
	{
		if (ptr->id == id) return ptr->lineNum;
		ptr = ptr->next;
	}
	return -1;
}

int main()
{
	hashTable t;
	assert(t.declare("abd", 1));
	assert(t.declare("abcd", 2));
	assert(t.declare("cadc", 3));
	assert(!t.declare("abd", 2));
	assert(t.find("abcd") == 2);
	assert(t.find("cacda") == -1);
	cout << "Passed all tests" << endl;
}
