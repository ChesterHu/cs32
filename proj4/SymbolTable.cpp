// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.
#include "SymbolTable.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

const int TABLE_SIZE = 100;
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

  // This class does the real work of the implementation.
class SymbolTableImpl
{
	public:
		SymbolTableImpl();
		~SymbolTableImpl();
		void enterScope();
		bool exitScope();
		bool declare(const string& id, int lineNum);
		int find(const string& id) const;
	private:
		  // scope, actually linked list
		struct Scope
		{
			hashTable table;
			Scope* next;
			Scope* prev;
			Scope() : next(nullptr), prev(nullptr) {}
			~Scope() { delete next; }
		};

		Scope* head;
		Scope* currScope;
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
	unsigned int hashVal = 0;
	for (int i = 0; i < key.size(); ++i)
		hashVal = hashVal * 101 + key[i] + 1;
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

SymbolTableImpl::SymbolTableImpl()
	: head(new Scope)
{
	currScope = head;
}

SymbolTableImpl::~SymbolTableImpl()
{
	delete head;
}

inline void SymbolTableImpl::enterScope()
{
	currScope->next = new Scope;
	currScope->next->prev = currScope;
	currScope = currScope->next;
}

inline bool SymbolTableImpl::exitScope()
{
	if (currScope->prev != nullptr)
	{
		currScope = currScope->prev;
		delete currScope->next;
		currScope->next = nullptr;
		return true;
	}
	return false;
}

inline bool SymbolTableImpl::declare(const string& id, int lineNum)
{
	return currScope->table.declare(id, lineNum);
}

int SymbolTableImpl::find(const string& id) const
{
	Scope* ptr = currScope;
	int lineNum = ptr->table.find(id);
	while (lineNum == -1 && ptr->prev != nullptr)
	{
		ptr = ptr->prev;
		lineNum = ptr->table.find(id);
	}
	return lineNum;
}
/*
int main()
{
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
