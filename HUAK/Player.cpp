#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************

bool getLineWithTwoIntegers(int& r, int& c)
{
    bool result(cin >> r >> c);
    if (!result)
        cin.clear();  // clear error state so can do more input operations
    cin.ignore(10000, '\n');
    return result;
}

// TODO:  You need to replace this with a real class declaration and
//        implementation.
class HumanPlayer : public Player
{
  public:
    HumanPlayer(string nm, const Game& g);
    virtual bool isHuman() const;
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
 : Player(nm, g)
{}

bool HumanPlayer::isHuman() const {return true;}

bool HumanPlayer::placeShips(Board& b)
{
    // need user's input.    
    int r, c;
    string dirInput;
    Direction dir;
    cout << name() << " must place " << game().nShips() << " ships" << endl; 
    b.display(false);
    for (int k = 0; k < game().nShips(); k++){
      cout << "Enter h or v for direction of " << game().shipName(k) << "(length " << game().shipLength(k) << "):";
      cin >> dirInput;
      cin.ignore(10000, '\n');
      while (dirInput != "h" && dirInput != "v"){
        cout << "Direction must be h or v." << endl;
        cout << "Enter h or v for direction of " << game().shipName(k) << "(length " << game().shipLength(k) << "):";
        cin >> dirInput;
        cin.ignore(10000, '\n');
        }
      if (dirInput == "h") {
        dir = HORIZONTAL;
        cout << "Enter row and column of leftmost call (e.g. 3 5):";
        while (!getLineWithTwoIntegers(r,c)){
          cout << "You must enter two integers." << endl;
          cout << "Enter row and column of leftmost call (e.g. 3 5):";
          }
        while (!b.placeShip(Point(r,c), k, dir)){
          cout << "The ship can not be placed there." << endl;
          cout << "Enter row and column of leftmost call (e.g. 3 5):";
          while (!getLineWithTwoIntegers(r,c)){
          cout << "You must enter two integers." << endl;
          cout << "Enter row and column of leftmost call (e.g. 3 5):";
          }
        }
        b.display(false);
      }
      else {
        dir = VERTICAL;
        cout << "Enter row and column of topmost call (e.g. 3 5):" ;
        while (!getLineWithTwoIntegers(r,c)){
          cout << "You must enter two integers." << endl;
          cout << "Enter row and column of topmost call (e.g. 3 5):";
          }
        while (!b.placeShip(Point(r,c), k, dir)){
          cout << "The ship can not be placed there." << endl;
          cout << "Enter row and column of topmost call (e.g. 3 5):";
          while (!getLineWithTwoIntegers(r,c)){
          cout << "You must enter two integers." << endl;
          cout << "Enter row and column of topmost call (e.g. 3 5):";
          }
        }
        b.display(false);
      }
    }
    return true;
}

Point HumanPlayer::recommendAttack()
{
  int r;
  int c;
  cout << "Enter the row and column to attack (e.g, 3 5):";
  while (!getLineWithTwoIntegers(r,c)){
    cout << "You must enter two integers." << endl;
    cout << "Enter the row and column to attack (e.g, 3 5):";
  }
  return Point(r, c);
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // HumanPlayer completely ignores the result of any attack
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
      // HumanPlayer completely ignores what the opponent does
}
//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
//typedef AwfulPlayer MediocrePlayer;
// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

class MediocrePlayer : public Player
{
  public:
    MediocrePlayer(string nm, const Game& g);
    virtual ~MediocrePlayer();
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    bool helper(Board& b, int placedNumShips, int totalNumShips, int rows, int cols);
  private:
    bool m_state;
    bool** hitBefore;
    Point m_lastCellAttacked;
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
 : Player(nm, g)
{
  m_state = false;
  m_lastCellAttacked = Point(0,0);
  hitBefore = new bool* [game().rows()];
  for (int i=0; i<game().rows(); i++) 
  {
    hitBefore[i] = new bool [game().cols()];
    for (int j=0; j<game().cols(); j++) 
    {
      hitBefore[i][j] = false;
    }
  }
}

MediocrePlayer::~MediocrePlayer()
{
  for (int i=0; i<game().rows(); i++)
    delete [] hitBefore[i];
  delete [] hitBefore;
}

bool MediocrePlayer::placeShips(Board& b)
{
  for (int i = 0; i < 50; i++)  // try 50 times to place ship
  {
    b.block();  // call the block function
	for (int i = 0; i < game().rows(); i++)
		for (int j = 0; j < game().cols(); j++)
			if (b.placeShip(Point(i, j), 0, HORIZONTAL) || b.placeShip(Point(i, j), 0, VERTICAL))
			{
				if (helper(b, 1, game().nShips(), game().rows(), game().cols()))
				{
				  b.unblock();    // call unblock function
				  return true;
				}
				b.unplaceShip(Point(i, j), 0, HORIZONTAL); b.unplaceShip(Point(i, j), 0, VERTICAL);
		    }
	b.clear();
  }

  return false;
}

bool MediocrePlayer::helper(Board& b, int placedNumShips, int totalNumShips, int rows, int cols)
{
  if (placedNumShips == totalNumShips)
    return true;
    // try place ships
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < cols; c++)
      for(int i = 0; i < totalNumShips; i++)
      {
          // try horizontal
        if (b.placeShip(Point(r, c), i, HORIZONTAL))
        {
          if (helper(b, placedNumShips + 1, totalNumShips, rows, cols))
            return true;
          b.unplaceShip(Point(r, c), i, HORIZONTAL);  
        }
          // try vertical
        if (b.placeShip(Point(r, c), i, VERTICAL))
        {
          if (helper(b, placedNumShips + 1, totalNumShips, rows, cols))
            return true;
          b.unplaceShip(Point(r, c), i, VERTICAL);  
        }       
      }

  return false;  
}

Point MediocrePlayer::recommendAttack()
{
    if (!m_state){
      while (true) {
        int r = randInt(game().rows());
        int c = randInt(game().cols());
        if (!hitBefore[r][c])
          return Point(r, c);     
      }
    }
    else { 
      for (int i = 0; i < 100; i++){
        int r = m_lastCellAttacked.r;
        int c = m_lastCellAttacked.c;
        int dire = randInt(4);
        int step = 1 + randInt(4);
        switch (dire){
          case 0: { 
            r = r + step;
            break;}
          case 1: {
            r = r - step;
            break;}
          case 2: {
            c = c + step;
            break;}
          case 3: {
            c = c - step;
            break;}
        }
        if (r >=0 && r <game().rows() && c>=0 && c< game().cols() && !hitBefore[r][c]) return Point(r, c);
      }
      m_state = false;
      return recommendAttack();
  }
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot,
                                     bool shotHit , bool shipDestroyed,
                                     int shipId)
{
  if (validShot){
    hitBefore[p.r][p.c] = true;
    if (shotHit && shipDestroyed)
      m_state = false;
    else if (shotHit && m_state == false) {m_state = true; m_lastCellAttacked = p;}
  }
}

void MediocrePlayer::recordAttackByOpponent(Point /* p */)
{
      // MediocrePlayer completely ignores what the opponent does
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
// typedef AwfulPlayer GoodPlayer;

class GoodPlayer : public Player
{
  public:
    GoodPlayer(string nm, const Game& g);
    virtual ~GoodPlayer();

	void clearMap();
	  // clear m_map
    virtual bool placeShips(Board& b);
	  // return true if all ships are placed in the board
	  // ships won't be placed in the same line. When one ship
	  // is placed, block the square in m_map, the square has the
	  // length as (2 * shipLength) and width as 5
	  // the ship is in the center of the square.
	bool placeShipRecur(Board& b, int placedNumShips, int totalShips, int nRows, int nCols);
	  // help function for placeShips
	void blockMap(Point topOrLeft, int shipId, Direction d, bool block);
	  // if block is true, then block the square with ship symbol, otherwise unblock square
	  // block m_map with a square, which is centered by the ship.
	  // block the line in the ship's direction.
	void recommendDirection(Point p);
	  // set m_state to the direction that has the longest '.' path
	  // if all directions have been attacked set m_state to NONE
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
	enum State {NONE, NORTH, SOUTH, WEST, EAST};

	State m_state;    // the attack state
	int m_hitLength;  // the hit length of the player
	stack<Point> m_centerPoints;  // record first hit of ships
	stack<Point> m_hitPoints;     // record hit points when state is not NONE
	char** m_map;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
	:Player(nm, g)
{
	int nRows = g.rows(), nCols = g.cols();
	
	m_map = new char* [nRows];
	for (int r = 0; r < nRows; r++)
		m_map[r] = new char [nCols];
	m_state = NONE;
	m_hitLength = 1;
}

GoodPlayer::~GoodPlayer()
{
	int nRows = game().rows(), nCols = game().cols();
	for (int r = 0; r < nRows; r++)
		delete [] m_map[r];
	delete [] m_map;
}

inline void GoodPlayer::clearMap()
{
	int nRows = game().rows(), nCols = game().cols();
	
	for (int r = 0; r < nRows; r++)
		for (int c = 0; c < nCols; c++)
			m_map[r][c] = '.';
}

void GoodPlayer::blockMap(Point topOrLeft, int shipId, Direction d, bool block)
{
	const Game& m_game = game();
	Point center;
	int shipLength = m_game.shipLength(shipId);
	int nRows = m_game.rows(), nCols = m_game.cols();
	char shipSymbol = m_game.shipSymbol(shipId);

	if (d == HORIZONTAL)  // find the center of the block square, and block/unblock
	{
		center.r = topOrLeft.r; center.c = topOrLeft.c + shipLength / 2;
		for (int c = 0; c < nCols; c++)  // block/unblock the line
		{
			if (block)
			{
				if (m_map[center.r][c] == '.')
					m_map[center.r][c] = shipSymbol;
			}
			else
			{
				if (m_map[center.r][c] == shipSymbol)
					m_map[center.r][c] = '.';
			}
		}

		for (int c = center.c - shipLength; c <= center.c + shipLength; c++)  // block/unblock the square
			for (int r = center.r - 2; r <= center.r + 2; r++)
				if (r >= 0 && r < nRows && c >=0 && c < nCols)
				{
					if(block)
					{
						if (m_map[r][c] == '.')
							m_map[r][c] = shipSymbol;
					}
					else
					{
						if (m_map[r][c] == shipSymbol)
							m_map[r][c] = '.';
					}
				}

	}
	else
	{
		center.r = topOrLeft.r + shipLength / 2; center.c = topOrLeft.c;
		for (int r = 0; r < nRows; r++)
		{
			if (block)
			{
				if (m_map[r][center.c] == '.')
					m_map[r][center.c] = shipSymbol;
			}
			else
			{
				if (m_map[r][center.c] == shipSymbol)
					m_map[r][center.c] = '.';
			}
		}

		for (int r = center.r - shipLength; r <= center.r + shipLength; r++)
			for (int c = center.c - 2; c <= center.c + 2; c++)
				if (r >= 0 && r < nRows && c >=0 && c < nCols)
				{
					if(block)
					{
						if (m_map[r][c] == '.')
							m_map[r][c] = shipSymbol;
					}
					else
					{
						if (m_map[r][c] == shipSymbol)
							m_map[r][c] = '.';
					}
				}	
	}
}

void GoodPlayer::recommendDirection(Point p)
{
	int nRows = game().rows(), nCols = game().cols();
	int maxLength = 0, currLength = 0;
	m_state = NONE;
	
	for (int r = p.r - 1; r >= 0 && m_map[r][p.c] == '.'; r--)  // NORTH
		currLength++;
	if (currLength > maxLength)
	{
		maxLength = currLength;
		m_state = NORTH;
		currLength = 0;
	}
	
	for (int r = p.r + 1; r < nRows && m_map[r][p.c] == '.'; r++)  // SOUTH
		currLength++;
	if (currLength > maxLength)
	{
		maxLength = currLength;
		m_state = SOUTH;
		currLength = 0;
	}

	for (int c = p.c - 1; c >= 0 && m_map[p.r][c] == '.'; c--)  // WEST
		currLength++;
	if (currLength > maxLength)
	{
		maxLength = currLength;
		m_state = WEST;
		currLength = 0;
	}

	for (int c = p.c + 1; c < nCols && m_map[p.r][c] == '.'; c++)  // EAST
	   currLength++;
	if (currLength > maxLength)
	{
		maxLength = currLength;
		m_state = EAST;
		currLength = 0;
	}
}

bool GoodPlayer::placeShips(Board& b)
{
	clearMap();
	for (int rand = 0; rand < 50; rand++)  // try 50 times
	{
		if(placeShipRecur(b, 0, game().nShips(), game().rows(), game().cols()))
		{
			clearMap();
			return true;
		}
	}
	return false;
}

bool GoodPlayer::placeShipRecur(Board& b, int placedNumShips, int totalShips, int nRows, int nCols)
{
	if (placedNumShips == totalShips)
		return true;

	int r, c;
	for (int rand = 0; rand < 50; rand++)  // try 50 times
	{
		r = randInt(nRows), c = randInt(nCols);
		if (randInt(2) == 1)  // try HORIZONTAL
		{
			if (m_map[r][c] == '.' && b.placeShip(Point(r, c), placedNumShips, HORIZONTAL))  // try place ship randomly in the map
			{
				blockMap(Point(r, c), placedNumShips, HORIZONTAL, true);  // block map
				if (placeShipRecur(b, placedNumShips + 1, totalShips, nRows, nCols))  // next level recursion
					return true;
				b.unplaceShip(Point(r, c), placedNumShips, HORIZONTAL);
				blockMap(Point(r, c), placedNumShips, HORIZONTAL, false);  // unblock map
			}
		}
		else
		{
			if (m_map[r][c] == '.' && b.placeShip(Point(r, c), placedNumShips, VERTICAL))  // try place ship randomly in the map {
			{
				blockMap(Point(r, c), placedNumShips, VERTICAL, true);  // block map
				if (placeShipRecur(b, placedNumShips + 1, totalShips, nRows, nCols))  // next level recursion
					return true;
				b.unplaceShip(Point(r, c), placedNumShips, VERTICAL);
				blockMap(Point(r, c), placedNumShips, VERTICAL, false);  // unblock map
			}
		}
	}
	return false;
}

Point GoodPlayer::recommendAttack()
{
	int nRows = game().rows(), nCols = game().cols();
	int r, c;
	if (m_state == NONE)  // if in state none, hit randomly in m_map[r][c] where (r + c) % 2 == 0
	{
		for (int i = 0; i < 200; ++i)
		{
			r = randInt(nRows); c = randInt(nCols);
			if((r + c) % 2 == 0 && m_map[r][c] == '.')
				return Point(r, c);
		}
		
		for (r = 0; r < nRows; r++)    // for the situation that smallest ship is 1 length
			for (c = 0; c < nCols; c++)
				if (m_map[r][c] == '.')
					return Point(r, c);
	}
	else
	{
		Point p = m_centerPoints.top();
		switch (m_state)
		{
			case NORTH : r = p.r - m_hitLength; c = p.c;
						 break;
			case SOUTH : r = p.r + m_hitLength; c = p.c;
						 break;
			case WEST :  r = p.r; c = p.c - m_hitLength;
						 break;
			case EAST :  r = p.r; c = p.c + m_hitLength;
						 break;
			case NONE :  break;
		}

		if (r < 0 || r >= nRows || c < 0 || c >= nCols || m_map[r][c] != '.')  // if invalid points recommend new direction
		{
			m_hitLength = 1;  // reset hit length to 1
			if (m_hitLength > 1)  // should in the opposite direction
			{
				if (m_state == NORTH)
					m_state = SOUTH;
				if (m_state == SOUTH)
					m_state = NORTH;
				if (m_state == WEST)
					m_state = EAST;
				if (m_state == EAST)
					m_state = WEST;
				return recommendAttack();
			}
			 // else find new direction from center point
			recommendDirection(p);
			if (m_state == NONE)  // if no direction to choose, pop the centerPoints
			{
				m_centerPoints.pop();
				if (!m_centerPoints.empty()) // if centerPoints is not empty
				   recommendDirection(m_centerPoints.top());
			}
			return recommendAttack();  // recommend attack	
		}

		return Point(r ,c);
	}
	return recommendAttack();
}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
	if (validShot)
	{
		m_map[p.r][p.c] = 'X';
		if (shotHit && shipDestroyed)  // if this hit destroyed a ship, 
		{
			if (m_centerPoints.empty())
				return;
			Point centerPoint = m_centerPoints.top();
			m_centerPoints.pop();
			m_hitPoints.push(p);
			int length = game().shipLength(shipId);  // the ship length the player destroyed
			Point hitPoint;
			while (!m_hitPoints.empty())
			{
				hitPoint = m_hitPoints.top();
				m_hitPoints.pop();
				switch (m_state)
				{
					case NONE  : break;
					case NORTH : if (hitPoint.c != centerPoint.c || hitPoint.r >= p.r + length)
									 m_centerPoints.push(hitPoint);
					case SOUTH : if (hitPoint.c != centerPoint.c || hitPoint.r <= p.r - length)
									 m_centerPoints.push(hitPoint);
					case WEST  : if (hitPoint.r != centerPoint.r || hitPoint.c >= p.c + length)
									 m_centerPoints.push(hitPoint);
					case EAST  : if (hitPoint.r != centerPoint.r || hitPoint.c <= p.c - length)
									 m_centerPoints.push(hitPoint);
				}
			}
			
			m_state = NONE;
			while (!m_centerPoints.empty())
			{
				recommendDirection(m_centerPoints.top());
				if (m_state == NONE)
					m_centerPoints.pop();
				else
					break;
			}

			if (m_state != NONE)
				m_hitPoints.push(m_centerPoints.top());
		}
		else if (shotHit)  // if hit a ship but not destroyed
		{
			m_hitPoints.push(p);
			if (m_state == NONE)
			{
				recommendDirection(p);
				if (m_state != NONE)
					m_centerPoints.push(p);
			}
			else
			{
				m_hitLength++;
			}
		}
	}
}

void GoodPlayer::recordAttackByOpponent(Point p)
{
	// TODO
}


//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}


