#include <iostream>   // for cout
#include <string>
#include <cassert>

using namespace std;
#include "animal.cpp"   // for testing

void animate(const Animal* a)
{
	    a->speak();
	    cout << "!  My name is " << a->name()
	         << ".  Watch me " << a->moveAction() << "!\n";
}

bool somePredicate(string s)
{
	return !s.empty();
}

void test_animal()
{
	    Animal* animals[4];
	    animals[0] = new Cat("Fluffy");
	      // Pigs have a name and a weight in pounds.  Pigs under 170
        // pounds oink; pigs weighing at least 170 pounds grunt.
	    animals[1] = new Pig("Napoleon", 190);
	    animals[2] = new Pig("Wilbur", 50);
	    animals[3] = new Duck("Daffy");

	    cout << "Here are the animals." << endl;
	    for (int k = 0; k < 4; k++)
        animate(animals[k]);

	      // Clean up the animals before exiting
	    cout << "Cleaning up." << endl;
	    for (int k = 0; k < 4; k++)
      	delete animals[k];
}

#include "linear.cpp"   // for testing 
void test_linear()
{

	do {
		string m_array[] = { "abc", "", "ad", "", "dd"};
		string m_array2[] = {"abc", "ad"};
		assert(!allTrue(m_array, 5));
		assert(countFalse(m_array, 5) == 2);
		assert(firstFalse(m_array, 5) == 1);
		assert(indexOfLeast(m_array, 5) == 1);
		assert(includes(m_array, 5, m_array2, 2));
	} while (0);

	do {
		string m_array[] = {"abc", "def", "cde", "bcd", "efg"};
		string m_array2[] = {"abc", "def", "cde", "bcd", "efg", "fgh"};
		assert(allTrue(m_array, 5));
		assert(countFalse(m_array, 5) == 0);
		assert(firstFalse(m_array, 5) == -1);
		assert(indexOfLeast(m_array, 5) == 0);
		assert(!includes(m_array, 5, m_array2, 6));
	} while (0);
	do {
		string m_array[] = { "", "bc", "ad", "de", "dd", "abc"};
		assert(firstFalse(m_array, 6) == 0);
		assert(countFalse(m_array, 6) == 1);
		assert(!allTrue(m_array, 6));
		assert(indexOfLeast(m_array, 6) == 0);
	} while (0);

	do {
		string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
		string a2[] = {"stan", "kenny", "cartman"};
		string a3[] = {"stan", "cartman", "butters"};
		string a4[] = {"kyle", "cartman", "cartman"};
		string a5[] = {"kyle", "butters", "kenny"};
		string a6[] = {"stan", "kenny", "kenny"};
		assert(includes(a1, 7, a2, 3));
		assert(includes(a1, 7, a3, 3));
		assert(includes(a1, 7, a4, 3));
		assert(!includes(a1, 7, a5, 3));
		assert(!includes(a1, 7, a6, 3));
	} while (0);
}

#include "maze.cpp"   // for testing
bool test_maze(int sr, int sc, int er, int ec) {
  char maze[10][10] = {{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
                       {'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X'},
                       {'X', 'X', '.', 'X', '.', 'X', 'X', 'X', 'X', 'X'},
                       {'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X'},
                       {'X', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X'},
                       {'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', '.', 'X'},
                       {'X', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X'},
                       {'X', '.', 'X', 'X', 'X', '.', 'X', 'X', '.', 'X'},
                       {'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X'},
                       {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

  return pathExists(maze, sr, sc, er, ec);
}

#include "tree.cpp"   // for testing
void test_tree()
{
	do {   // test countIncludes
		string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
		string a2[] = {"stan", "cartman", "butters"};
		string a3[] = {"stan", "kenny", "cartman"};
		string a4[] = {"kyle", "cartman", "butters"};
		string a5[] = {"kenny", "stan", "cartman"};
		assert(countIncludes(a1, 7, a2, 3) == 2);
		assert(countIncludes(a1, 7, a3, 3) == 1);
		assert(countIncludes(a1, 7, a4, 3) == 3);
		assert(countIncludes(a1, 7, a5, 3) == 0);
	} while (0);

	do {   // test order
		string a[] = {"d", "e", "f", "c", "a", "g", "b", "a", "b", "c", "e", "d"};
		order(a, 12);
		for (int i = 0; i < 12; ++i)
			cout << a[i] << endl;	
	} while (0);
}

int main()
{
	test_animal();
	test_linear();
	do {
		assert(test_maze(6, 4, 1, 1));
		assert(test_maze(8, 8, 1, 1));
		assert(!test_maze(8, 1, 1, 1));
		assert(!test_maze(8, 1, 8, 8));
		assert(test_maze(5, 8, 1, 1));	
	} while (0);
	test_tree();

	cout << "Passed all tests" << endl;
}
