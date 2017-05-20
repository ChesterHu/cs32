#ifndef PICTURE_INCLUDED
#define PICTURE_INCLUDED

using namespace std;
class Circle
{
	public:
		Circle(double x, double y, double r)
			: m_x(x), m_y(y), m_r(r)
		{}

		void printCircle()
		{
			cout << m_x << ' ' << m_y << ' ' << m_r << endl;
		}
	private:
		double m_x;
		double m_y;
		double m_r;
};

class Picture
{
	public:
		Picture(int capacity)
			: m_nItems(0), m_capacity(capacity)
		{
			m_items = new Circle* [capacity];
		}

		void addCircle(double r, double x, double y)
		{
			if (m_nItems < m_capacity)
			{
				m_items[m_nItems] = new Circle(x, y, r);
				m_nItems++;
			}
		}

		~Picture();
		Picture(const Picture& other);
		void printPicture()
		{
			for (int i = 0; i < m_nItems; ++i)
				m_items[i]->printCircle();
		}
	private:
		Circle** m_items;
		int m_nItems;
		int m_capacity;
};

Picture::~Picture()
{
	for (int i = 0; i < m_nItems; ++i)
		delete m_items[i];
	delete [] m_items;
}

Picture::Picture(const Picture& other)
{
	m_nItems = other.m_nItems;
	m_capacity = other.m_capacity;
	m_items = new Circle* [m_capacity];
	for (int i = 0; i < m_nItems; ++i)
	{
		m_items[i] = new Circle(0, 0, 0);
		*m_items[i] = *(other.m_items[i]);
	}
}

#endif // PICTURE_INCLUDED
