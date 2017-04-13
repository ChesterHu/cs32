#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
  m_rows = nRows;
  m_cols = nCols;

  // Initialize grid status
  for (int i = 0; i < m_rows; ++i)
    for (int j = 0; j < m_cols; ++j)
      m_grid[i][j] = EMPTY;
}

void History::display() const {
  char displayGrid[m_rows][m_cols];

  // Fill displayGrid with dots (empty) and char A ~ Z
  for (int r = 0; r < m_rows; ++r)
    for (int c = 0; c < m_cols; ++c) {
      if (m_grid[r][c] == 0)
        displayGrid[r][c] = '.';
      else {
        displayGrid[r][c] = (char)m_grid[r][c] + 64;
      }
    }

  // Draw the grid
  clearScreen();
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_cols; ++c)
      cout << displayGrid[r][c];
    cout << endl;
  }
  cout << endl;

  // Print message and return to Game
}

bool History::record(int r, int c) {
  if (r <= m_rows && r > 0 && c <= m_cols && c > 0) {
    if (m_grid[r - 1][c - 1] < 26)
      m_grid[r - 1][c - 1]++;
    return true;
  }
  return false;
}
