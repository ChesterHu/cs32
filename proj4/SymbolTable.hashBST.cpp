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
	Node* left;
	Node* right;
	Node** parent;
	Node(const string& new_id, int new_line, int new_Scope) 
		: id(new_id), left(nullptr), right(nullptr)
	{
		m_Scopes.push_back(Pair(new_line, new_Scope)); 
	}
	~Node()
	{
		delete left;
		delete right;
	}
};
  // a hashTable for string
class hashTable
{
	public:
		hashTable()
		{
			for (int i = 0; i < TABLE_SIZE; ++i)
				bucket[i] = nullptr;
		}
		~hashTable()
		{
			for (int i = 0; i < TABLE_SIZE; ++i)
				delete bucket[i];
		}

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

  // return the hash value of a key
inline int hashF(const string& key)
{
	unsigned long long hashVal = 0;
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
		ptr = (id < (*ptr)->id) ? &((*ptr)->left) : &((*ptr)->right);
	}
	*ptr = new Node(id, lineNum, scopeNum);
	(*ptr)->parent = ptr;
	return *ptr;
}

inline int hashTable::find(const string& id) const
{
	Node* ptr = bucket[hashF(id)];
	while (ptr != nullptr)
	{
		if (ptr->id == id)
			return (ptr->m_Scopes.empty()) ? -1 : ptr->m_Scopes.back().lineNum;
		ptr = (id < ptr->id) ? ptr->left : ptr->right;
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
			currId[i]->m_Scopes.pop_back();
			if (currId[i]->m_Scopes.empty())
			{
				// move left subtree right most leaf to top
				Node* currNode = currId[i]->left;
				if (currNode == nullptr)
				{
					currNode = currId[i];
					if (currNode->right != nullptr)
						currNode->right->parent = currNode->parent;
					*(currId[i]->parent) = currId[i]->right;
				}
				else
				{
					while (currNode->right != nullptr)
						currNode = currNode->right;
					if (currNode->left != nullptr)
						currNode->left->parent = currNode->parent;
					*(currNode->parent) = currNode->left;
					*(currId[i]->parent) = currNode;
					currNode->left = currId[i]->left; currNode->right = currId[i]->right;
					if (currId[i]->left != nullptr)
						currId[i]->left->parent = &(currNode->left);
					if (currId[i]->right != nullptr)
						currId[i]->right->parent = &(currNode->right);
				}
				currId[i]->left = currId[i]->right = nullptr;
				*(currId[i]->parent) = nullptr;
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
