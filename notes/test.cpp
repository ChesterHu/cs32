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

int main() {
	student a(2, 8);
	cout << a.get_age() << endl;
	return 0;
}
