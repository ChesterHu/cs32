#include <list>
#include "Set.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

class Coord
{
	public:
		Coord(int r, int c) : m_r(r), m_c(c) {}
		Coord() : m_r(0), m_c(0) {}
		double r() const { return m_r; }
		double c() const { return m_c; }
	private:
		double m_r;
		double m_c;
};

vector<int> destroyedOnes;

class Movie
{
	public:
		Movie(int r) : m_rating(r) {}
		~Movie() { destroyedOnes.push_back(m_rating); }
		int rating() const { return m_rating; }
	private:
		int m_rating;
};

void removeBad(list<Movie*>& li)
{
	list<Movie*>::iterator iter = li.begin();
	Movie* p;
	while (iter != li.end())
	{
		if ((*iter)->rating() < 50)
		{
			p = *iter;
			iter = li.erase(iter);
			delete p;
		}
		else
		{
			iter++;
		}
	}
}

void removeOdds(vector<int>& v)
{
	// first move all odds elements to the tail of vector
	// the oddsStart records start position of odds integer
	// then erase all elements start by oddsStart.

	int oddsStart = v.size();
	int unknown = 0;
	int temp = 0;
	while (unknown < oddsStart)
	{
		if (v[unknown] % 2 == 1)
		{
			temp = v[unknown];
			v[unknown] = v[oddsStart - 1];
			v[oddsStart] = temp;
			oddsStart--;
		}
		else
			unknown++;
	}

	v.erase(v.begin() + oddsStart, v.end());
}

class Domain
{
  public:
    Domain(string lbl) : m_label(lbl) {}
    string label() const { return m_label; }
    const vector<Domain*>& subdomains() const { return m_subdomains; }
    void add(Domain* d) { m_subdomains.push_back(d); }
    ~Domain();
  private:
    string m_label;
    vector<Domain*> m_subdomains;
};

Domain::~Domain()
{
    for (size_t k = 0; k < m_subdomains.size(); k++)
        delete m_subdomains[k];
}

void listAll(string path, const Domain* d) // two-parameter overload
{
	const vector<Domain*>& domains = d->subdomains();
    if (!domains.empty())
		for (vector<Domain*>::const_iterator it = domains.begin(); it != domains.end(); it++)
			listAll((*it)->label() + ((path.empty()) ?  "": ".") + path, *it);
	else
		cout << path << endl;
}

void listAll(const Domain* d)  // one-parameter overload
{
    if (d != nullptr)
        listAll(d->label(), d);
}

void test()
{
	{
		Domain* d1 = new Domain("ucla");
		d1->add(new Domain("cs"));
		d1->add(new Domain("ee"));
		d1->add(new Domain("math"));
		Domain* d2 = new Domain("caltech");
		d2->add(new Domain("math"));
		d2->add(new Domain("cs"));
		Domain* d3 = new Domain("edu");
		d3->add(d1);
		d3->add(d2);
		Domain* d4 = new Domain("com");
		d4->add(new Domain("microsoft"));
		d4->add(new Domain("apple"));
		Domain* d5 = new Domain("biz");
		Domain* root = new Domain("");
		root->add(d3);
		root->add(d4);
		root->add(d5);
		listAll(root);
		cout << "====" << endl;
		listAll(d2);
		cout << "====" << endl;
		listAll(d5);
		delete root;
	}

	{
		int a[10] = { 85, 80, 30, 35, 70, 75, 20, 15, 90, 10 };
		list<Movie*> x;
		for (int k = 0; k < 10; k++)
				x.push_back(new Movie(a[k]));
		assert(x.size() == 10 && x.front()->rating() == 85 && x.back()->rating() == 10);
		removeBad(x);
		assert(x.size() == 5 && destroyedOnes.size() == 5);
		vector<int> v;
		for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
		{
				Movie* mp = *p;
				v.push_back(mp->rating());
		}
			// Aside:  In C++11, the above loop could be
			//     for (auto p = x.begin(); p != x.end(); p++)
			//     {
			//         Movie* mp = *p;
			//         v.push_back(mp->rating());
			//     }
			// or    
			//     for (auto p = x.begin(); p != x.end(); p++)
			//     {
			//         auto mp = *p;
			//         v.push_back(mp->rating());
			//     }
			// or    
			//     for (Movie* mp : x)
			//         v.push_back(mp->rating());
			// or    
			//     for (auto mp : x)
			//         v.push_back(mp->rating());
		sort(v.begin(), v.end());
		int expect[5] = { 70, 75, 80, 85, 90 };
		for (int k = 0; k < 5; k++)
			assert(v[k] == expect[k]);
		sort(destroyedOnes.begin(), destroyedOnes.end());
		int expectGone[5] = { 10, 15, 20, 30, 35 };
		for (int k = 0; k < 5; k++)
			assert(destroyedOnes[k] == expectGone[k]);
		for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
			delete *p;  // Deallocate remaining movies.
	}

	{
		int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
		vector<int> x(a, a+8);  // construct x from the array
		assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
		removeOdds(x);
		assert(x.size() == 4);
		sort(x.begin(), x.end());
		int expect[4] = { 2, 4, 6, 8 };
		for (int k = 0; k < 4; k++)
			assert(x[k] == expect[k]);
	}

	{
		int a[8] = { 2, 8, 2, 6, 6, 4, 4, 2 };
		vector<int> x(a, a+8);  // construct x from the array
		assert(x.size() == 8 && x.front() == 2 && x.back() == 2);
		removeOdds(x);
		assert(x.size() == 8);
		sort(x.begin(), x.end());
	}
	
	{
		int a[8] = { 2, 8, 8, 6, 7, 4, 4, 1 };
		vector<int> x(a, a+8);  // construct x from the array
		assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
		removeOdds(x);
		assert(x.size() == 6);
		sort(x.begin(), x.end());
		int expect[6] = { 2, 4, 4, 6, 8, 8 };
		for (int k = 0; k < 6; k++)
			assert(x[k] == expect[k]);
	}
	{
	    Set<int> si;
	    Set<string> ss;
	    assert(si.empty());
	    assert(ss.empty());
	    assert(si.size() == 0);
	    assert(ss.size() == 0);
	    assert(si.insert(10));
	    assert(ss.insert("hello"));
	    assert(si.contains(10));
	    assert(ss.contains("hello"));
	    int i;
	    assert(si.get(0, i)  &&  i == 10);
	    string s;
	    assert(ss.get(0, s)  &&  s == "hello");
	    assert(si.erase(10));
	    assert(ss.erase("hello"));
	    Set<int> si2(si);
	    Set<string> ss2(ss);
	    si.swap(si2);
	    ss.swap(ss2);
	    si = si2;
	    ss = ss2;
	    unite(si,si2,si);
	    unite(ss,ss2,ss);
	    subtract(si,si2,si);
	    subtract(ss,ss2,ss);
	}

	{
		Set<int> a;
		a.insert(1);
		a.erase(1);
		Set<string> b;
		b.insert("a");
		b.erase("a");
		Set<double> c;
		c.insert(1.2);
		c.erase(1.2);
	} 

	{
		Set<int> a;
		Set<int> b;
		Set<int> c;
		for (int i = 0; i < 10; ++i)
			a.insert(i);
		for (int i = 5; i < 10; ++i)
			b.insert(i);
		unite(a, b, c);
		assert(c.size() == 10);
		subtract(a, b, c);
		assert(c.size() == 5);
	};
}

int main()
{
	test();
	Set<Coord> sc;
	// sc.insert(Coord(4, -4));	// error!
	cout << "\nPassed all test" << endl;
}

