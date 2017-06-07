// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.
#include "SymbolTable.h"
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

const int TABLE_SIZE = 20000;

  // struct to store lineNum and scope
struct Pair
{
	int lineNum;
	int scope;
	Pair(int newLine, int newScope) : lineNum(newLine), scope(newScope) {}
};

  // struct for store identifier and it's scope
struct Node
{
	string id;
	vector<Pair> m_Scopes;
	Node* next;
	Node(string new_id, int new_line, int new_Scope) 
		: id(new_id), next(nullptr) 
	{
		m_Scopes.push_back(Pair(new_line, new_Scope)); 
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
inline int hashF(const string& key)
{
	unsigned int hashVal = 0;
	for (int i = 0; i < key.size(); ++i)
		hashVal = hashVal * 101 + key[i] + 1;
	return hashVal % TABLE_SIZE;
}

inline Node* hashTable::declare(const string& id, const int& lineNum, int scopeNum)
{
	Node** ptr = &bucket[hashF(id)];  // get pointer points to the pointer of the hash values bucket
	while (*ptr != nullptr)
	{
		if ((*ptr)->id == id)  // if find the node with the same id
		{
			if ((*ptr)->m_Scopes.empty() || (*ptr)->m_Scopes.back().scope != scopeNum)
			{
				(*ptr)->m_Scopes.push_back(Pair(lineNum, scopeNum));
				return *ptr;
			}
			else
				return nullptr;
		}
		ptr = &((*ptr)->next);
	}
	*ptr = new Node(id, lineNum, scopeNum);
	return *ptr;
}

inline int hashTable::find(const string& id) const
{
	Node* ptr = bucket[hashF(id)];
	while (ptr != nullptr)
	{
		if (ptr->id == id)
			return (ptr->m_Scopes.empty()) ? -1 : ptr->m_Scopes.back().lineNum;
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
		for (int i = 0; i < currId.size(); ++i)
		{
			currId[i]->m_Scopes.pop_back();
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
/*
int main()
{
	hashTable ht;
	assert(ht.declare("abc", 1, 0));
	assert(ht.declare("abc", 2, 2));
	assert(!ht.declare("abc", 3, 2));
	assert(ht.find("abc") == 2);

	SymbolTable st;
	assert(st.declare("alpha", 1));
	assert(st.declare("beta", 2));
	assert(st.declare("p1", 3));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.declare("p2", 4));
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.declare("p3", 5));
	assert(st.find("gamma") == -1);  // Error!  gamma hasn't been declared
	assert(st.declare("f", 6));
	st.enterScope();
	assert(st.declare("beta", 7));
	assert(st.declare("gamma", 8));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 7);    // the beta declared in line 7
	assert(st.find("gamma") == 8);   // the gamma declared in line 8
	st.enterScope();
	assert(st.declare("alpha", 13));
	assert(st.declare("beta", 14));
	assert(!st.declare("beta", 15)); // Error! beta already declared
	assert(st.find("alpha") == 13);  // the alpha declared in line 13
	assert(st.exitScope());
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.find("beta") == 7);    // the beta declared in line 7
	st.enterScope();
	assert(st.declare("beta", 21));
	assert(st.find("beta") == 21);   // the beta declared in line 21
	assert(st.exitScope());
	assert(st.exitScope());
	assert(st.declare("p4", 25));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.declare("p5", 26));
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.declare("p6", 27));
	assert(st.find("gamma") == -1); // Error! gamma is not in scope
	assert(st.declare("main", 28));
	st.enterScope();
	assert(st.declare("beta", 29));
	assert(st.find("beta") == 29);   // the beta declared in line 29
	assert(st.find("f") == 6);       // the f declared in line 6
	assert(st.exitScope());
}
*/
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
