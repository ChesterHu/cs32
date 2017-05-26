#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
      // We prevent a Game object from being copied or assigned
    BoardImpl(const BoardImpl&) = delete;
    BoardImpl& operator=(const BoardImpl&) = delete;
    ~BoardImpl();

  private:
      // TODO:  Decide what private members you need.  Here's one that's likely
      //        to be useful:
    const Game& m_game;
    char board[MAXROWS][MAXCOLS];
    int* hit;
    int numOfCurrentShips;
};

BoardImpl::BoardImpl(const Game& g)
 : m_game(g)
{
    for (int i=0; i< m_game.rows(); i++){
        for (int j=0; j< m_game.cols(); j++){
            board[i][j] = '.';
        }
    }
    hit = new int[m_game.nShips()];  // hit describes the health of each ship. If it has been placed, assign length to the hit.
    //each time, hit it once, hit--;
    for (int i=0; i< m_game.nShips(); i++){
        hit[i] = 0;
    }
    numOfCurrentShips = 0;
}

BoardImpl::~BoardImpl()
{
    delete [] hit;
}

void BoardImpl::clear()
{
    for (int i=0; i< m_game.rows(); i++){
        for (int j=0; j< m_game.cols(); j++){
            board[i][j] = '.';
        }
    }
    // This compiles, but may not be correct
}

void BoardImpl::block()
{
      // Block cells with 50% probability
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)
            {
                board[r][c] = 'o'; // TODO:  Replace this with code to block cell (r,c)
            }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
        {
            if (board[r][c] == 'o') board[r][c] = '.'; // TODO:  Replace this with code to unblock cell (r,c) if blocked
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    // if the shipId is invalid, return false
    if (shipId < 0 || shipId >= m_game.nShips()) return false;
    // if the ship would be partly or fully outside the board, return false
    if (!m_game.isValid(topOrLeft)) return false;
    Point bottomOrRight;  // set up a new point
    if (dir == HORIZONTAL) {        
        bottomOrRight.r = topOrLeft.r;
        bottomOrRight.c = topOrLeft.c + m_game.shipLength(shipId)- 1;
        if (!m_game.isValid(bottomOrRight)) return false;
    }
    if (dir == VERTICAL) {
        bottomOrRight.r = topOrLeft.r + m_game.shipLength(shipId)- 1;
        bottomOrRight.c = topOrLeft.c;
        if (!m_game.isValid(bottomOrRight)) return false;
    }
    // if the ship would overlap an already-placed ship or overlap one or more positions that were blocked by a previous
    // call to the block function, return false
    int cur_x;
    int cur_y;
    for (int i=0; i< m_game.shipLength(shipId); i++){
        if (dir == HORIZONTAL) {
            cur_x = topOrLeft.r;
            cur_y = topOrLeft.c + i;
        }
        else {
            cur_x = topOrLeft.r + i;
            cur_y = topOrLeft.c;
        }
        if (board[cur_x][cur_y] != '.') return false;
    }
    // if the ship with that ship ID has previously been placed on this Board and not
    // yet been unplaced since its most recent placement, return false;
    if (hit[shipId] != 0) return false;
    // ready to place the ship
    for (int i=0; i< m_game.shipLength(shipId); i++){
        if (dir == HORIZONTAL) {
            cur_x = topOrLeft.r;
            cur_y = topOrLeft.c + i;
        }
        else {
            cur_x = topOrLeft.r + i;
            cur_y = topOrLeft.c;
        }
        board[cur_x][cur_y] = m_game.shipSymbol(shipId);
    }
    hit[shipId] = m_game.shipLength(shipId);
    numOfCurrentShips++;
    return true;
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    // if the shipId is invalid, return false
    if (shipId < 0 || shipId >= m_game.nShips() || hit[shipId] == 0) return false;
    // if the board does not contain the entire ship at the indicated locations, return false
    Point cur = topOrLeft; 
    for (int i=0; i< m_game.shipLength(shipId); i++){
        if (!m_game.isValid(cur) || board[cur.r][cur.c] != m_game.shipSymbol(shipId)) return false;
        if (dir == HORIZONTAL) {
            cur.r = cur.r;
            cur.c = cur.c + 1;
        }
        else {
            cur.r = cur.r + 1;
            cur.c = cur.c;
        }
    }
    // ready to unplace
    cur = topOrLeft; 
    for (int i=0; i< m_game.shipLength(shipId); i++){
        board[cur.r][cur.c] = '.';
        if (dir == HORIZONTAL) {
            cur.r = cur.r;
            cur.c = cur.c + 1;
        }
        else {
            cur.r = cur.r + 1;
            cur.c = cur.c;
        }      
    }
    hit[shipId] = 0;
    numOfCurrentShips--;
    return true; // This compiles, but may not be correct
}

void BoardImpl::display(bool shotsOnly) const
{
    cout << "  ";
    for (int i=0; i<m_game.cols(); i++){
        cout << i ;
    }
    cout << endl;
    for (int i=0; i<m_game.rows(); i++){
        cout << i << " ";
        for (int j=0; j<m_game.cols(); j++){
            if (!shotsOnly) {
                cout << board[i][j];
            }
            else {
                if (board[i][j] == 'X' || board[i][j] == 'o') cout << board[i][j];
                else cout << '.';
            }
        }
        cout << endl;
        
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    // if the attack point is outside of the board area, return false
    if (!m_game.isValid(p)) return false;
    // if an attack is made on a previously attacked location, return false;
    if (board[p.r][p.c] == 'X' || board[p.r][p.c] == 'o') return false;
    if (board[p.r][p.c] == '.') {
        shotHit = false;
        board[p.r][p.c] = 'o';
    }
    else {
        shotHit = true;
        for (int i=0; i<m_game.nShips(); i++){
            if (m_game.shipSymbol(i) == board[p.r][p.c]){
                shipId = i;
                hit[i]--;
                board[p.r][p.c] = 'X';
                if (hit[i] == 0) {
                    shipDestroyed = true;
                    numOfCurrentShips--;
                }
                else shipDestroyed = false;
                break;
            }
        }
    }  
    return true; // This compiles, but may not be correct
}

bool BoardImpl::allShipsDestroyed() const
{
    if (numOfCurrentShips == 0) return true;
    return false; // This compiles, but may not be correct
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
