#include <iostream>
using namespace std;

void func(int* p, int& other)
{
	p = &other;
}

int main()
{
	int* p;
	int a = 1, b = 2;
	p = &a;
	cout << "before passed to function, p points to: " << *p << endl;
	cout << "pass p to func(int* p, &b), which let p point to b" << endl;
	func(p, b);	
	cout << "now p points to: " << *p << endl;

	return 0;
}
