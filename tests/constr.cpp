#include <iostream>
#include <string>
using namespace std;

class student
{
	public:
		student(int x) 
		{
			cout << "I'm not default constructor" << endl;
			age = x;
		}
	/*	
		student() 
		{
			cout << "I'm default constructor" << endl;
			age = 2;
		}*/
		student(const student& other)
		{
			cout << "I'm copy constructor" << endl;
			age = other.age;
		}

		student& operator=(const student& rhs)
		{
			cout << "I'm assign operator" << endl;
			age = rhs.age;
			return *this;
		}
	private:
		int age;
};

class school
{
	public:
		school(string name, int size)
		{
			cout << "I'm constructor of school" << endl;
			m_name = name;
			m_numStudents = size;
			//m_students = new student[size];
		}
		school(const school& other)
			:sb(10)
		{
			m_name = other.m_name;
			m_numStudents = other.m_numStudents;
			//m_students = new student[m_numStudents];
			//for (int i = 0; i < m_numStudents; ++i)
				//m_students[i] = other.m_students[i];
		}
		int size()
		{
			return m_numStudents;
		}

	private:
		student sb;
		string m_name;
		//student* m_students;
		int m_numStudents;
};

int main()
{
	school a("UCLA", 10);
	//school b(a);
	//cout << b.size() << endl;
	return 0;
}
