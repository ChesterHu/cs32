#include <iostream>
using namespace std;

void func(char m_array[][2])
{
	m_array[0][0] = '.';
}

int main()
{
	char a[2][2] = {
		{'x','x'},
		{'x','x'}
	};
	func(a);
	cout << a[0][0] << endl;
}
