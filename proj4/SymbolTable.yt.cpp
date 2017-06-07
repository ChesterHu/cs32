// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.

#include "SymbolTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

  // This class does the real work of the implementation.

class SymbolTableImpl
{
  public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
  private:
    unordered_map<string, vector<int>> mp;
    vector<unordered_set<string>> v;
};

void SymbolTableImpl::enterScope()
{
      // Extend the id vector with an empty string that
      // serves as a scope entry marker.
      v.push_back(unordered_set<string> {});
}

bool SymbolTableImpl::exitScope()
{
      // Remove ids back to the last scope entry.
    if (v.size() == 1)
      return false;
    for (auto x: v[v.size()-1])
      mp[x].pop_back();
    v.pop_back();
    return true;
}

bool SymbolTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
        return false;

      // Check for another declaration in the same scope.
      // Return if found, break out if encounter the scope
      // entry marker.
    if (v.size() == 0)
      v.push_back(unordered_set<string> {});
    if (v[v.size()-1].count(id))
      return false;
    mp[id].push_back(lineNum);
    v[v.size()-1].insert(id);
    return true;
}

int SymbolTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

      // Search back for the most recent declaration still
      // available.

    auto p = mp.find(id);
    if (p == mp.end())
      return -1;
    if (p->second.size() == 0)
      return -1;
    return p->second[p->second.size()-1];
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
