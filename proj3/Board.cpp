#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
	~BoardImpl();
    void clear();
	
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
	  // prevent copy constructor and assignment operator
	BoardImpl(const BoardImpl&) = delete;
	BoardImpl& operator=(const BoardImpl&) = delete;

  private:
      // TODO:  Decide what private members you need.  Here's one that's likely
      //        to be useful:
    const Game& m_game;
	int* m_placedShips; // dynamic bool array, m_placedShips[i] == true means the ship has been placed
	char** m_Board;      // 2-dimention dynamic array to record board
	int m_health;        // total health of this board
};

// Function Implementation
///////////////////////////////////////////////////////////

BoardImpl::BoardImpl(const Game& g)  // modified
 : m_game(g), m_health(0)
{
	int nShips = m_game.nShips();
	 
      // initialize m_Board
    m_Board = new char*[m_game.rows()];
	for (int i = 0; i < m_game.rows(); i++)
		m_Board[i] = new char[m_game.cols()];

	  // initialize m_placedShips
	m_placedShips = new int[nShips];
}

BoardImpl::~BoardImpl()
{
	for (int i = 0; i < m_game.rows(); i++)
		delete [] m_Board[i];
	delete [] m_Board;
	delete [] m_placedShips;
}

void BoardImpl::clear()  // modified
{
      // clear board
	for (int i = 0; i < m_game.rows(); i++)
		for (int j = 0; j < m_game.cols(); j++)
			m_Board[i][j] = '.';
      // clear all ships
    for (int k = 0; k < m_game.nShips(); k++)
        m_placedShips[k] = 0;
}

void BoardImpl::block()  // modified
{
      // Block cells with 50% probability
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)
            {
				m_Board[r][c] = 'X';
            }
}

void BoardImpl::unblock()  // modified
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
        {
			if (m_Board[r][c] == 'X')
				m_Board[r][c] = '.';
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)  // modified
{
	int r = topOrLeft.r, c = topOrLeft.c;  // start coordinate
	int length = m_game.shipLength(shipId);   // ship length
	char symbol = m_game.shipSymbol(shipId);           // ship symbol
	int maxRows = m_game.rows(), maxCols = m_game.cols(); // bounds

	if (m_placedShips[shipId] > 0 || r < 0 || r >= maxRows || c < 0 || c >= maxCols)
		return false;
	if (dir == HORIZONTAL)  // check horizontally
	{
		for (int i = 0; i < length; i++)
			if (c + i >= maxCols || m_Board[r][c + i] != '.')
				return false;
		for (int i = 0; i < length; i++)
			m_Board[r][c + i] = symbol;
	}
	else                    // check vertically
	{
		for (int i = 0; i < length; i++)
			if (c + i >= maxRows || m_Board[r + i][c] != '.')
				return false;
		for (int i = 0; i < length; i++)
			m_Board[r + i][c] = symbol;
	}
	
	m_health += length;
	m_placedShips[shipId] += length;
	return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
	int r = topOrLeft.r, c = topOrLeft.c;
	int maxRows = m_game.rows(), maxCols = m_game.cols();
	int length = m_game.shipLength(shipId);
	char symbol = m_game.shipSymbol(shipId);

	if (m_placedShips[shipId] == 0 || r < 0 || r >= maxRows || c < 0 || c >= maxCols)
		return false;

	if (dir == HORIZONTAL && c + length - 1 < maxCols && m_Board[r][c + length - 1] == symbol)  // try to remove ship
	{
		for (int i = 0; i < length; i++)
			m_Board[r][c + i] = '.';
		m_placedShips[shipId] = false;
		m_health -= m_game.shipLength(shipId);
		return true;
	}
	else if (r + length - 1 < maxRows && m_Board[r + length - 1][c] == symbol)
	{
		for (int i = 0; i < length; i++)
			m_Board[r + i][c] = '.';
		m_placedShips[shipId] -= length;
		m_health -= length;
		return true;
	}

    return false; // This compiles, but may not be correct
}

void BoardImpl::display(bool shotsOnly) const  // modified
{
    int maxRows = m_game.rows(), maxCols = m_game.cols();
	cout << "  ";
	for (int i = 0; i < maxCols; i++)
		cout << i;
	cout << endl;

	for (int i = 0; i < maxRows; i++)
	{
		cout << i << ' ';
		for (int j = 0; j < maxCols; j++)
		{
			if (shotsOnly && m_Board[i][j] != 'X' && m_Board[i][j] != 'o')
				cout << '.';
			else
				cout << m_Board[i][j];
		}
		cout << endl;
	}
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)  // modified
{
	int maxRows = m_game.rows(), maxCols = m_game.cols();
	int r = p.r, c = p.c;
    shotHit = shipDestroyed = false;
	if (r < 0 || r >= maxRows || c < 0 || c >= maxCols || m_Board[r][c] == 'o' || m_Board[r][c] == 'X')
		return false;

	if (m_Board[r][c] == '.')
	{
		m_Board[r][c] = 'o';
	}
	else
	{
		for(int i = 0; i < m_game.nShips(); i++)
		{
			if (m_game.shipSymbol(i) == m_Board[r][c])  // its the ship to hit
			{
				m_health--;
				shotHit = true;
				m_Board[r][c] = 'X';
                shipId = i;
                shipDestroyed = (--m_placedShips[i] == 0) ? true : false;
                return true;
			}
		}
	}
	
	return true;
}

bool BoardImpl::allShipsDestroyed() const  // modified
{
    return m_health == 0;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
