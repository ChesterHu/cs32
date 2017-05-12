#include <iostream>
using namespace std;

int& min(int &a, int &b)
{
	return (a < b) ? a : b;
}

int main()
{
	int a = 1;
	int b = 2;
	cout << &min(a, b) << endl;
	cout << &a << endl;
}

