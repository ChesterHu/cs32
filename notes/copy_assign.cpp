#include <iostream>
using namespace std;

class student
{
  public:
    student()
    {
      cout << "default constructor" << endl;
    }

    student(int x)
    {
      cout << "constructor" << endl;
      m_score = x;
    }

    student(const student &other)
    {
      cout << "copy constructor" << endl;
      m_score = other.m_score;
    }

    student& operator=(const student& rhs)
    {
      cout << "assignment operator" << endl;
      m_score = rhs.m_score;
      return *this;
    }

  private:
    int m_score;
};

student func()
{
  student g(15);
  return g;
}

int main()
{
  //func();
  student a(10);
  student e = a; // copy constructor
  return 0;
}
