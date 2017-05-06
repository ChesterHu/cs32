#include <iostream>
#include <cassert>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr, sc) to (er, ec)
// through the maze; return false otherwise. Use recursion


bool test(int sr, int sc, int er, int ec) {
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

int main()
{
	assert(test(6, 4, 1, 1));
	assert(test(8, 8, 1, 1));
	assert(!test(8, 1, 1, 1));
	assert(!test(8, 1, 8, 8));
	assert(test(5, 8, 1, 1));	
	cout << "Passed all test" << endl;
}

// function implementation
///////////////////////////////////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	if (sr == er && sc == ec)   // if start location is end location return true
		return true;
	if (sr > 9 || sr < 0 || sc > 9 || sc < 0 || maze[sr][sc] == 'X')
		return false;
	maze[sr][sc] = 'X';   // update the start location as visited
	for (int i = 0; i < 2; ++i)
		for (int j = 1 - i; j < 2 - i; ++j)
			if (pathExists(maze, sr + i, sc + j, er, ec) || pathExists(maze, sr - i, sc - j, er, ec))
				return true;
	return false;
}
