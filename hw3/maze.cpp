bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr, sc) to (er, ec)
// through the maze; return false otherwise. Use recursion

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
