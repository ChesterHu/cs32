#include "SymbolTable.h"
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>

#include <iostream> // !!!!!!!!!!!!!!!!!!!!!!!!!
using namespace std;

const int NUMBEROFBUCKS = 20000;
const unsigned int HASHCOEF = 16777619;
const unsigned int HASHBASE = 2166136261U;

class SymbolTableImpl
{
	struct identifier
	{
		string name;
		list<int> line;
		list<int> scopeIdx;
		identifier* next;
		identifier(string _name) : name(_name), next(nullptr) {}
	};

public:
	SymbolTableImpl();
	void enterScope();
	bool exitScope();
	bool declare(const string& id, int lineNum);
	int find(const string& id) const;
	~SymbolTableImpl();

//	void printTable() const;  // !!!!!!!!!!!!!!!!!!!!!!!!!


private:
	int hashCode(const string& id) const;

	int curIdx;
	identifier* buck[NUMBEROFBUCKS];
	vector<vector<identifier*>> id_vec;
};

SymbolTableImpl::SymbolTableImpl() 
{
	curIdx = 0;
	id_vec.push_back(vector<identifier*>());
	for (int i = 0; i < NUMBEROFBUCKS; i++)
		buck[i] = nullptr;
}

SymbolTableImpl::~SymbolTableImpl()
{
	for (int i = 0; i < id_vec.size(); i++)
		for (int j = 0; j < id_vec[i].size(); j++)
			delete id_vec[i][j];
}

void SymbolTableImpl::enterScope()
{
	curIdx++;
	id_vec.push_back(vector<identifier*>());
}

bool SymbolTableImpl::exitScope()
{
	if (id_vec.size() <= 1)
		return false;
	identifier* id;
	// initial scope cannot be left
	for (int i = 0; i < id_vec.back().size(); i++)
	{
		id = id_vec.back()[i];
		id->line.pop_back();
		id->scopeIdx.pop_back();
		if (id->line.empty())
		{
			int h = hashCode(id->name);
			identifier* p = buck[h];
			identifier* q = buck[h];
			if (buck[h]->name == id->name)
			{
				buck[h] = p->next;
				delete p;
			}
			else
			{
				while (p->name != id->name)
				{
					q = p;
					p = p->next;
				}
				q->next = p->next;
				delete p;
			}
		}
	}
	curIdx--;
	id_vec.pop_back();
	return true;
}

int SymbolTableImpl::hashCode(const string& id) const
{
	/*
	unsigned long hash = 5381;
	int c;

	for (const char& c : id) 
	{
		hash = ((hash << 5) + hash) + (int)c;
	}
	return hash % NUMBEROFBUCKS;
	*/
	unsigned int h = HASHBASE;
	for (int i = 0; i != id.size(); i++)
		h = (h + id[i]) * HASHCOEF;
	return (h % NUMBEROFBUCKS);
	
}


bool SymbolTableImpl::declare(const string& id, int lineNum)
{
	if (id.empty())
		return false;

	int h = hashCode(id);
	// buck[h] is null
	if (buck[h] == nullptr)
	{
		buck[h] = new identifier(id);
		buck[h]->line.push_back(lineNum);
		buck[h]->scopeIdx.push_back(curIdx);
		id_vec.back().push_back(buck[h]);
		return true;
	}
	identifier* p = buck[h];
	identifier* q = buck[h];

	while (p != nullptr)
	{
		if (p->name == id)
		{
			// same declaration in the scope
			if (!p->scopeIdx.empty() && p->scopeIdx.back() == curIdx)
				return false;
			// no declaration in the scope
			else
			{
				p->line.push_back(lineNum);
				p->scopeIdx.push_back(curIdx);
				id_vec.back().push_back(p);
				return true;
			}
		}
		else
		{
			q = p;
			p = p->next;
		}
			
	}
	// declaratio of first time 
	if (p == nullptr)
	{
		q->next = new identifier(id);
		p = q->next;
		p->line.push_back(lineNum);
		p->scopeIdx.push_back(curIdx);
		id_vec.back().push_back(p);
	}
	return true;
}

int SymbolTableImpl::find(const string& id) const
{
	if (id.empty())
		return -1;

	identifier* p = buck[hashCode(id)];
	while (p != nullptr)
	{
		if ((p->name) == id)
			if (!p->line.empty())
				return p->line.back();
			else
				return -1;		
		p = p->next;
	}
	return -1;
}

/*
void SymbolTableImpl::printTable() const
{
	for (int i = 0; i < NUMBEROFBUCKS; i++)
	{
		identifier* p = buck[i];
		while (p != nullptr)
		{
			if (!p->line.empty())
				cout << p->name << ' ' << p->line.back() << endl;
			p = p->next;
		}
	}
	cout << "============================" << endl;
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
/*
void SymbolTable::printTable() const
{
	m_impl->printTable();
}
*/