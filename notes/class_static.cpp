#include <iostream>
using namespace std;

class student
{
	public:
		student() { num_students++; sid = 1;}
		static int how_many() { return num_students; }
		static int test() { return sid; }
	private:
		static int num_students;   // declaration
		int sid;
};

int student::num_students = 0;   // definition

int main()
{
	student a;
	student b;
	cout << a.how_many() << ' ' << b.how_many() << endl;
	student c;
	cout << a.how_many() << endl;
}
