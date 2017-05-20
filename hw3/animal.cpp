// class declarations
///////////////////////////////////////////////////////////
// Animal abstract base class
class Animal
{
	public:
		Animal(string name);
		virtual ~Animal();

		string name() const;   // return data member m_name
		virtual string moveAction() const;   // move action of derived class
		virtual void speak() const = 0;   // speak action of derived class
	private:
		string m_name;
};

// Cat derived class of Animal
class Cat : public Animal
{
	public:
		Cat(string name);
		virtual ~Cat();

		virtual void speak() const;
};

// Pig derived class of Animal
class Pig : public Animal
{
	public:
		Pig(string name, int pounds);
		virtual ~Pig();

		virtual void speak() const;
	private:
		int m_pounds;
};

// Duck derived class of Animal
class Duck : public Animal
{
	public:
		Duck(string name);
		virtual ~Duck();

		virtual string moveAction() const;
		virtual void speak() const;
};
// class implementation
///////////////////////////////////////////////////////////

// Animal
// constructor
Animal::Animal(string name)
	: m_name(name)
{}

// deconstructor
Animal::~Animal()
{}

// name() function
string Animal::name() const
{
	return m_name;
}

// move action of animal
string Animal::moveAction() const
{
	return "walk";
}
// Cat
// constructor
Cat::Cat(string name)
	: Animal(name)
{}

// deconstructor
Cat::~Cat()
{
	cout << "Destroying " << name() << " the cat" << endl;
}

// speak function of cat
void Cat::speak() const
{
	cout << "Meow";
}

// Pig
// constructor
Pig::Pig(string name, int pounds)
	: Animal(name), m_pounds(pounds)
{}

// deconstructor
Pig::~Pig()
{
	cout << "Destroying " << name() << " the pig" << endl;
}


// speak action of Pig
void Pig::speak() const
{
	if (m_pounds < 170)
		cout << "Oink";
	else
		cout << "Grunt";
}

// Duck
// constructor
Duck::Duck(string name)
	: Animal(name)
{}

// deconstructor
Duck::~Duck()
{
	cout << "Destroying " << name() << " the duck" << endl;
}

// overiding move action of Duck
string Duck::moveAction() const
{
	return "swim";
}

// speak action of Duck
void Duck::speak() const
{
	cout << "Quack";
}
