// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.
#include "SymbolTable.h"
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

  // struct to store lineNum and scope
struct Pair
{
	int lineNum;
	int scope;
	Pair(int newLine, int newScope) : lineNum(newLine), scope(newScope) {}
};

  // strut for Trie node
struct Node
{
	bool isWord;
	Node* children[52];
	vector<Pair> scopes;

	Node(bool b)
		: isWord(b)
	{
		for (int i = 0; i < 52; ++i)
			children[i] = nullptr;
	}

	~Node()
	{
		for (int i = 0; i < 52; ++i)
			delete children[i];
	}
};
class Trie
{
	public:
		Trie() { root = new Node(false); }
		~Trie() { delete root; }

		Node* declare(const string& id, int lineNum, int scopeNum);
		int find(const string& id) const;
	private:
		Node* root;
};

Node* Trie::declare(const string& id, int lineNum, int scopeNum)
{
	Node** ptr = &root;
	for (int i = 0; i < id.size(); ++i)
	{
		ptr = &((*ptr)->children[id[i] <= 90 ? id[i] - 39 : id[i] - 97]);
		if (*ptr == nullptr)
			*ptr = new Node(false);
	}
	if (!(*ptr)->isWord || (*ptr)->scopes.back().scope != scopeNum)
	{
		(*ptr)->isWord = true;
		(*ptr)->scopes.push_back(Pair(lineNum, scopeNum));
		return *ptr;
	}
	return nullptr;
}

int Trie::find(const string& id) const
{
	Node* ptr = root;
	for (int i = 0; i < id.size(); ++i)
	{
		ptr = ptr->children[id[i] <= 90 ? id[i] - 39 : id[i] - 97];
		if (ptr == nullptr)
			return -1;
	}
	if (ptr->isWord && !ptr->scopes.empty())
		return ptr->scopes.back().lineNum;
	return -1;
}

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
		vector<vector<Node*> > idVector;
		Trie tree;
};

// function implementation
///////////////////////////////////////////////////////////

void SymbolTableImpl::enterScope()
{
	idVector.push_back(vector<Node*>());
}

bool SymbolTableImpl::exitScope()
{
	if (idVector.size() == 1)
		return false;
	vector<Node*>& currId = idVector.back();
	int len = currId.size();

	for (int i = 0; i < len; ++i)
		currId[i]->scopes.pop_back();
	idVector.pop_back();
	return true;
}

bool SymbolTableImpl::declare(const string& id, int lineNum)
{
	Node* res = tree.declare(id, lineNum, idVector.size());
	if (res != nullptr)
	{
		idVector.back().push_back(res);
		return true;
	}
	return false;
}

int SymbolTableImpl::find(const string& id) const
{
	return tree.find(id);
}
/*
int main()
{
	Trie tree;
	assert(tree.declare("abc", 1, 1));
	assert(tree.declare("abc", 10, 1) == nullptr);
	assert(tree.find("abc") == 1);
	assert(tree.find("abcd") == -1);
	
	SymbolTable st;
	assert(st.declare("alpha", 1));
	assert(st.declare("beta", 2));
	assert(st.declare("pa", 3));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.declare("pb", 4));
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.declare("pc", 5));
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
	assert(st.declare("pd", 25));
	assert(st.find("alpha") == 1);   // the alpha declared in line 1
	assert(st.declare("pe", 26));
	assert(st.find("beta") == 2);    // the beta declared in line 2
	assert(st.declare("pf", 27));
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
