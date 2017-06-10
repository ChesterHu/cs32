#include <string>
#include <iostream>
using namespace std;

class student
{
	public:
		student(int x, int y)
			:age(x)
		{
			id = y;
		}
		int get_age()
		{
			return age;
		}
	private:
		const int age;
		int id;
};

int& compare(int& a, int& b)
{
	return (a < b) ? a : b;
}

int main() {
	student a(2, 8);
	cout << a.get_age() << endl;
	int i = 2, j = 3;
	compare(i, j);
	return 0;
}
