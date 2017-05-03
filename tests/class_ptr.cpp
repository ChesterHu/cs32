#include <iostream>
using namespace std;

class Shape
{
	public:
		Shape(double x, double y)
			: m_x(x), m_y(y)
		{}
		virtual void move(double xnew, double ynew)
		{
			m_x = xnew;
			m_y = ynew;
		}
		double x()
		{ return m_x; }
	  double y()
		{ return m_y; }
	 	 
	private:
		double m_x;
	  double m_y;
};

class Rectangle : public Shape
{
	public:
		Rectangle(double x, double y)
			: Shape(x, y)
		{}
};

int main()
{
	Rectangle r(1, 2);
  r.move(2, 3);
	cout << r.x() << ' ' << r.y() << endl;
	return 0;
}
