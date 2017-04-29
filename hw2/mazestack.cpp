#include <iostream> // Use cout and cerr.
#include <stack>    // Use C++ builtin structure stack.
using namespace std;

class Coord 
{
public:
  Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
  int r() const { return m_r; }
  int c() const { return m_c; }

private:
  int m_r;
  int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr, sc) to (er, ec)
// through the maze; return false otherwise.

int main() 
{
  Coord a(0, 1);
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
	
	cout << pathExists(maze, 6, 4, 6, 1) << endl;
	return 0;
}


// Function implementation
////////////////////////////////////////////////////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) 
{
	stack<Coord> coordStack;          // record possible places
	coordStack.push(Coord(sr, sc));   // push start place into stack
	maze[sr][sc] = 'X';               // update the maze to indicate this place has been visited

	while (!coordStack.empty())                // while stack is not empty, keep doing DFS search
	{
		int curr_r = coordStack.top().r();  // get the place algo intend to explore 
		int curr_c = coordStack.top().c();
		coordStack.pop();                   // pop out the top coordinate
		cout << curr_r << ' ' << curr_c << endl;	
		if (curr_r == er && curr_c == ec)   // if this is the end place, return true
			return true;
		
		if (curr_r - 1 >= 0 && maze[curr_r - 1][curr_c] == '.')  // explore NORTH, push place if algo can move NORTH
		{
			coordStack.push(Coord(curr_r - 1, curr_c));
			maze[curr_r - 1][curr_c] = 'X';
		}
		if (curr_c + 1 < 10 && maze[curr_r][curr_c + 1] == '.')  // explore EAST, push place if algo can move EAST
		{
			coordStack.push(Coord(curr_r, curr_c + 1));
			maze[curr_r][curr_c + 1] = 'X';
		}
		if (curr_r + 1 < 10 && maze[curr_r + 1][curr_c] == '.')  // explore SOUTH, push place if algo can move NORTH
		{
			coordStack.push(Coord(curr_r + 1, curr_c));
			maze[curr_r + 1][curr_c] = 'X';
		}
		if (curr_c - 1 >= 0 && maze[curr_r][curr_c - 1] == '.')  // explore WEST, push place if algo can move WEST
		{
			coordStack.push(Coord(curr_r, curr_c - 1));
			maze[curr_r][curr_c - 1] = 'X';
		}
	}

  return false;
}
