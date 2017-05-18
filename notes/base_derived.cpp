#include <iostream>
using namespace std;

class A
{
	public:
		A() : m_id(10) {}
	private:
		int m_id;
};

class B : public A
{
	public:
	 	B() : m_age(20) {}
	private:
		int m_age;
};

int main()
{
	A* a = new A;
	B* b = new A;

	// cout << a->m_id << endl;
	delete a;
	delete b;
}
