// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.
#include "SymbolTable.h"
#include <string>
#include <vector>
using namespace std;

const int TABLE_SIZE = 20000;
const unsigned int HASHCOEF = 16777619;
const unsigned int HASHBASE = 2166136261U;
  // struct to store lineNum and scope
struct Pair
{
	int lineNum;
	int scope;
	Pair(int newLine, int newScope) : lineNum(newLine), scope(newScope) {}
	Pair() {}
};

  // struct for store identifier and it's scope
struct Node
{
	Pair m_Scopes[4];
	int m_size;
	
	string id;
	Node* next;
	Node** prev;
	Node(const string& new_id, int new_line, int new_Scope) 
		: id(new_id), next(nullptr), prev(nullptr), m_size(1)
	{
		m_Scopes[0] = Pair(new_line, new_Scope); 
	}
};

  // a hashTable for string
class hashTable
{
	public:
		hashTable();
		~hashTable();

		Node* declare(const string& id, const int& lineNum, int scopeNum);
		int find(const string& id) const;
	private:
		Node* bucket[TABLE_SIZE];
};

  // This class does the real work of the implementation.
class SymbolTableImpl
{
	public:
		SymbolTableImpl() { idVector.push_back(vector<Node*>()); }
		void enterScope();
		bool exitScope();
		bool declare(const string& id, int lineNum);
		int find(const string& id) const;
	private:
		  // use a vector of pointers point to Nodes
		vector<vector<Node*> > idVector;
		// vector<vector<string> > idVector;
		hashTable table;
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
	Node* ptr;
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		while (bucket[i] != nullptr)
		{
			ptr = bucket[i];
			bucket[i] = bucket[i]->next;
			delete ptr;
		}
	}
}

  // return the hash value of a key
inline int hashF(const string& id)
{
	unsigned int h = HASHBASE;
	for (int i = 0; i != id.size(); i++)
		h = (h + id[i]) * HASHCOEF;
	return (h % TABLE_SIZE);
	
}

Node* hashTable::declare(const string& id, const int& lineNum, int scopeNum)
{
	Node** ptr = &bucket[hashF(id)];  // get pointer points to the pointer of the hash values bucket
	while (*ptr != nullptr)
	{
		if ((*ptr)->id == id)  // if find the node with the same id
		{
			if ((*ptr)->m_size == 0 || (*ptr)->m_Scopes[(*ptr)->m_size - 1].scope != scopeNum)
			{
				(*ptr)->m_Scopes[(*ptr)->m_size++] = Pair(lineNum, scopeNum);
				return *ptr;
			}
			else
				return nullptr;
		}
		ptr = &((*ptr)->next);
	}
	*ptr = new Node(id, lineNum, scopeNum);
	(*ptr)->prev = ptr;
	return *ptr;
}

inline int hashTable::find(const string& id) const
{
	Node* ptr = bucket[hashF(id)];
	while (ptr != nullptr)
	{
		if (ptr->id == id)
			return (ptr->m_size == 0) ? -1 : ptr->m_Scopes[ptr->m_size - 1].lineNum;
		ptr = ptr->next;
	}
	return -1;
}

inline void SymbolTableImpl::enterScope()
{
	idVector.push_back(vector<Node*>());
}

inline bool SymbolTableImpl::exitScope()
{
	if (idVector.size() > 1)
	{
		vector<Node*>& currId = idVector.back();
		int len = currId.size();
		for (int i = 0; i < len; ++i)
		{
			if (--currId[i]->m_size == 0)
			{
				*(currId[i]->prev) = currId[i]->next;
				if (currId[i]->next != nullptr)
					currId[i]->next->prev = currId[i]->prev;
				delete currId[i];
			}
		}
		idVector.pop_back();
		return true;
	}
	return false;
}

inline bool SymbolTableImpl::declare(const string& id, int lineNum)
{
	Node* result = table.declare(id, lineNum, idVector.size());
	if (result != nullptr)
	{
		idVector.back().push_back(result);
		return true;
	}
	return false;
}

inline int SymbolTableImpl::find(const string& id) const
{
	return table.find(id);
}
//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
    m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
    delete m_impl;
}

void SymbolTable::enterScope()
{
    m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
    return m_impl->exitScope();
}

bool SymbolTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int SymbolTable::find(const string& id) const
{
    return m_impl->find(id);
}
