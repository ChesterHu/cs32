#include <queue>    // Use C++ builtin structure queue.

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

// Function implementation
////////////////////////////////////////////////////////////////////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) 
{
	std::queue<Coord> coordQueue;          // record possible places
	coordQueue.push(Coord(sr, sc));   // push start place into queue
	maze[sr][sc] = 'X';               // update the maze to indicate this place has been visited

	while (!coordQueue.empty())             // while queue is not empty, keep doing DFS search
	{
		int curr_r = coordQueue.front().r();  // get the place algo intend to explore 
		int curr_c = coordQueue.front().c();
		coordQueue.pop();                      // pop out the top coordinate
		// std::cout << curr_r << ' ' << curr_c << endl;   // for problem 4	
		if (curr_r == er && curr_c == ec)   // if this is the end place, return true
			return true;
		
		if (curr_r - 1 >= 0 && maze[curr_r - 1][curr_c] == '.')  // explore NORTH, push place if algo can move NORTH
		{
			coordQueue.push(Coord(curr_r - 1, curr_c));
			maze[curr_r - 1][curr_c] = 'X';
		}
		if (curr_c + 1 < 10 && maze[curr_r][curr_c + 1] == '.')  // explore EAST, push place if algo can move EAST
		{
			coordQueue.push(Coord(curr_r, curr_c + 1));
			maze[curr_r][curr_c + 1] = 'X';
		}
		if (curr_r + 1 < 10 && maze[curr_r + 1][curr_c] == '.')  // explore SOUTH, push place if algo can move NORTH
		{
			coordQueue.push(Coord(curr_r + 1, curr_c));
			maze[curr_r + 1][curr_c] = 'X';
		}
		if (curr_c - 1 >= 0 && maze[curr_r][curr_c - 1] == '.')  // explore WEST, push place if algo can move WEST
		{
			coordQueue.push(Coord(curr_r, curr_c - 1));
			maze[curr_r][curr_c - 1] = 'X';
		}
	}

  return false;
}
