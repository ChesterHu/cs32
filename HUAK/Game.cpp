#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
private:
    int m_row;
    int m_col;
    int m_nShips; 

    struct Ship
    {
        int shipID;
        int shipLength;
        char shipSymbol;
        string shipName;
    };
    
    Ship m_ship[100];
      
};

void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols; 
    m_nShips = 0;
    for (int i=0; i< 100; i++){
        m_ship[i].shipLength = 0;
        m_ship[i].shipSymbol = ' ';
        m_ship[i].shipName = "";
    }
    // This compiles but may not be correct
}

int GameImpl::rows() const
{
    return MAXROWS;  // return the MAXROWS
}

int GameImpl::cols() const
{
    return MAXCOLS;  // return the MAXCOLS
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    int Id = m_nShips;
    m_ship[Id].shipLength = length;
    m_ship[Id].shipSymbol = symbol;
    m_ship[Id].shipName = name;
    m_nShips++;
    return true;  // This compiles but may not be correct
}

int GameImpl::nShips() const
{

    return m_nShips;  // This compiles but may not be correct
}

int GameImpl::shipLength(int shipId) const
{
    return m_ship[shipId].shipLength;  // This compiles but may not be correct
}

char GameImpl::shipSymbol(int shipId) const
{
    return m_ship[shipId].shipSymbol;  // This compiles but may not be correct
}

string GameImpl::shipName(int shipId) const
{
    return m_ship[shipId].shipName;  // This compiles but may not be correct
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause = true)
{
    bool shotHit;
    bool shipDestroyed;
    int shipId;
    bool validShot;

    // display the second player's board
    cout << p1->name() << "'s turn.  Board for " << p2->name() << ":" << endl;
    b2.display(p1->isHuman());

    // make the first player's attack
    Point p = p1->recommendAttack();
    validShot = b2.attack(p, shotHit, shipDestroyed, shipId);
    if (!validShot) cout << p1->name() << " wasted a shot at (" << p.r << "," << p.c << ")." << endl;
    else{
        cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and ";
        if (!shotHit) {
            cout << "missed, resulting in:" << endl;
        }
        else {
            if (!shipDestroyed) {
                cout << "hit something, resulting in:" << endl;
                }
            else {
                cout << "destroyed the " << shipName(shipId) << ", resulting in:" << endl;
            } 
        }
        b2.display(p1->isHuman());
    }
    p1->recordAttackResult(p, validShot, shotHit, shipDestroyed, shipId);
    p1->recordAttackByOpponent(p);
    // test whether p1 wons
    if (b2.allShipsDestroyed()) {     
        cout << p1->name() << "won the game!" << endl;
        if (p2->isHuman()) {
            cout << "Board for" << p1->name() << ":" << endl;
            b1.display(true);
        }
        return p1;
    }
    if (shouldPause) waitForEnter();
    return play(p2,p1,b2,b1,shouldPause);
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);

    //if a player being unable to place the ships on their board, return nullptr.
    if (p1->placeShips(b1) == false || p2->placeShips(b2) == false) return nullptr;
    
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

