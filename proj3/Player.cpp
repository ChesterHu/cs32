#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>

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
// typedef AwfulPlayer HumanPlayer;

class HumanPlayer : public Player
{
	public:
		HumanPlayer(string nm, const Game& g);
		virtual ~HumanPlayer();
		virtual bool isHuman() const;
		  // place ships for human player
		virtual bool placeShips(Board& b);
		virtual Point recommendAttack();
    	virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                        bool shipDestroyed, int shipId);
    	virtual void recordAttackByOpponent(Point p);
		  // get direction for human player to place ships
		bool getLineWithDirection(Direction& d) const;
		  // delete copy constructor and assignment operator
		HumanPlayer(const HumanPlayer&) = delete;
		HumanPlayer& operator=(const HumanPlayer&) = delete;
};

HumanPlayer::HumanPlayer(string nm, const Game& g)
	: Player(nm, g)
{}

HumanPlayer::~HumanPlayer()
{}

bool HumanPlayer::isHuman() const
{
	return true;
}

bool HumanPlayer::placeShips(Board& b)
{
	const Game& m_game = Player::game();
	int k = 0;
	Direction dir;
	int r, c;
	
	cout << Player::name() << " must place "
		 << m_game.nShips() << " ships.\n";
	b.display(false);  // display the map
	while (k < m_game.nShips())
	{
		cout << "Enter h or v for direction of "
			 << m_game.shipName(k) << " (length"
			 << m_game.shipLength(k) << "): ";
		if (!getLineWithDirection(dir))  // try to get direction
		{
			cout << "Direction must be h or v.\n";
			continue;
		}

		while (true)
		{
			cout << "Enter row and column of " 
			     << ( (dir == HORIZONTAL) ? "leftmost " : "topmost " )
			     << "cell (e.g. 3 5): ";
			if (!getLineWithTwoIntegers(r, c))  // try to get coordinate
			{
				cout << "You must enter two integers.\n";
				continue;
			}
			if (!b.placeShip(Point(r, c), k, dir))  // try to place ship
			{
				cout << "The ship can not be placed there.\n";
				continue;
			}
			break;
		}
		k++;
		b.display(false);  // display the map
	}

	return true;
}

Point HumanPlayer::recommendAttack()
{
	int r, c;
	while (true)
	{
		cout << "Enter the row and column to attack (e.g, 3 5): ";
		if(!getLineWithTwoIntegers(r, c))
		{
			cout << "You must enter two integers.\n";
			continue;
		}
		break;
	}
	return Point(r, c);
}

void HumanPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{}

void HumanPlayer::recordAttackByOpponent(Point p)
{}

bool HumanPlayer::getLineWithDirection(Direction& d) const
{
	string input;
	cin >> input;
    cin.ignore(10000, '\n');
	if (input[0] == 'h')
		d = HORIZONTAL;
	else if (input[0] == 'v')
		d = VERTICAL;
	else
		return false;
	return true;
}
//*********************************************************************
//  MediocrePlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
// typedef AwfulPlayer MediocrePlayer;

class MediocrePlayer : public Player
{
	public:
		MediocrePlayer(string nm, const Game& g);
		virtual ~MediocrePlayer();
		virtual bool placeShips(Board& b);
		bool placeShipsRecursively(Board& b, int placedNumShips, int totalNumShips, int maxRows, int maxCols);
		virtual Point recommendAttack();
		virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
		virtual void recordAttackByOpponent(Point p);

		MediocrePlayer(const MediocrePlayer&) = delete;
		MediocrePlayer& operator=(const MediocrePlayer&) = delete;
	private:
		bool** hitMap;   // true after hit
		Point hitPoint;  // if (-1,-1), it's in state 1, otherwise state 2
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
	: Player(nm, g), hitPoint(-1, -1)
{
	hitMap = new bool* [game().rows()];
	for (int i = 0; i < game().rows(); ++i)
	{
		hitMap[i] = new bool [game().cols()];
		for (int j = 0; j < game().cols(); j++)
			hitMap[i][j] = false;
	}
}

MediocrePlayer::~MediocrePlayer()
{
	for (int i = 0; i < game().rows(); i++)
		delete [] hitMap[i];
	delete [] hitMap;
}

bool MediocrePlayer::placeShips(Board& b)
{
	const Game& m_game = game();
	for (int k = 0; k < 50; ++k)  // try 50 times to place ship
	{
		b.block();
		if (placeShipsRecursively(b, 0, m_game.nShips(), m_game.rows(), m_game.cols()))
		{
			b.unblock();
			return true;
		}
		b.unblock();
	}

	return false;
}

bool MediocrePlayer::placeShipsRecursively(Board& b, int placedNumShips, int totalNumShips, int maxRows, int maxCols)
{
	if (placedNumShips == totalNumShips)
		return true;
	  // try place ships
	for (int r = 0; r < maxRows; r++)
		for (int c = 0; c < maxCols; c++)
			for(int i = 0; i < totalNumShips; i++)
			{
				  // try horizontal
				if (b.placeShip(Point(r, c), i, HORIZONTAL))
				{
					if (placeShipsRecursively(b, placedNumShips + 1, totalNumShips, maxRows, maxCols))
						return true;
					b.unplaceShip(Point(r, c), i, HORIZONTAL);	
				}
				  // try vertical
				if (b.placeShip(Point(r, c), i, VERTICAL))
				{
					if (placeShipsRecursively(b, placedNumShips + 1, totalNumShips, maxRows, maxCols))
						return true;
					b.unplaceShip(Point(r, c), i, VERTICAL);	
				}				
			}

	return false;
	
}

Point MediocrePlayer::recommendAttack()  // TODO
{
	int nRows = game().rows(), nCols = game().cols();
	int r = hitPoint.r, c = hitPoint.c;
	if (r < 0)  // state 1
	{
		while (true)  // try random points
		{
			r = randInt(nRows); c = randInt(nCols);
			if (!hitMap[r][c])  // not hit before
				return Point(r, c);
		}
	}
	else  // state 2
	{
		int new_r, new_c;
		for (int i = 0; i < 160; ++i)  // 6.1287e-05
		{
			new_r = r; new_c = c;
			if (randInt(2) == 0)
				new_r = r - 4 + randInt(9);
			else	
				new_c = c - 4 + randInt(9);
			if (new_r >= 0 && new_r < nRows && new_c >= 0 && new_c < nCols && !hitMap[new_r][new_c])
				return Point(new_r, new_c);
		}
	}

	hitPoint.r = -1;  // if the ship's length > 5, set state to 1
	return recommendAttack();
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
	if (validShot)
	{
		hitMap[p.r][p.c] = true;             // record valid shot
		if (shipDestroyed)
			hitPoint.r = -1;                 // reset to state 1
		else if (shotHit && hitPoint.r < 0)  // if hit a ship and it's in state 1
			hitPoint = p;
	}
}

void MediocrePlayer::recordAttackByOpponent(Point p)
{}  // MediocrePlayer ignores opponent's attach

// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
// typedef AwfulPlayer GoodPlayer;

  // GoodPlayer will only randomly hit those board[i][j]
  // such that (i + j) % minLength == 0
  // where minLength is the minimum length of battleship in the game.

class GoodPlayer : public Player
{
	public:
		GoodPlayer(string nm, const Game& g);
		virtual ~GoodPlayer();
		
		virtual bool placeShips(Board& b);
		bool placeShipsRecursively(Board& b, int placedNumShips, int totalNumShips, int maxRows, int maxCols);
		virtual Point recommendAttack();
		virtual void recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId);
		virtual void recordAttackByOpponent(Point p);

		GoodPlayer(const GoodPlayer&) = delete;
		GoodPlayer& operator=(const GoodPlayer&) = delete;
	
	private:
		char** hitMap;
		int direction;            // 0 is state 1; 1, 2, 3, 4: NORTH, SOUTH, WEST, EAST
		int m_step;
		int stepLength;
		vector<int>  shipsOfOpponent;     // recored the length of opponent's ships, sinkedShips[i] == -1, means ship i is sinked.
		vector<Point> centerPoints;           // center points
		vector<Point> hitPoints;          // record hit points when it's in state 2
};


GoodPlayer::GoodPlayer(string nm, const Game& g)
	: Player(nm, g), direction(0), m_step(g.rows()), stepLength(1)
{
	int nRows = g.rows(), nCols = g.cols();
	
	hitMap = new char* [nRows];
	for (int r = 0; r < nRows; ++r)
	{
		hitMap[r] = new char [nCols];
		for (int c = 0; c < nCols; ++c)
			hitMap[r][c] = '.';
	}
}

GoodPlayer::~GoodPlayer()
{
	for (int i = 0; i < game().rows(); i++)
		delete [] hitMap[i];
	delete [] hitMap;
}


bool GoodPlayer::placeShips(Board& b)
{
	const Game& m_game = game();

	for (int i = 0; i < m_game.nShips(); i++)  // initialize the steps and all ship length
	{
		shipsOfOpponent.push_back(m_game.shipLength(i));
		if (shipsOfOpponent.back() < m_step)
			m_step = shipsOfOpponent.back();
	}

	for (int k = 0; k < 50; ++k)  // try 50 times to place ship
	{
		b.block();
		if (placeShipsRecursively(b, 0, m_game.nShips(), m_game.rows(), m_game.cols()))
		{
			b.unblock();
			return true;
		}
		b.unblock();
	}

	return false;
}

bool GoodPlayer::placeShipsRecursively(Board& b, int placedNumShips, int totalNumShips, int maxRows, int maxCols)
{
	if (placedNumShips == totalNumShips)
		return true;
	  // try place ships
	for (int r = 0; r < maxRows; r++)
		for (int c = 0; c < maxCols; c++)
			for(int i = 0; i < totalNumShips; i++)
			{
				  // try horizontal
				if (b.placeShip(Point(r, c), i, HORIZONTAL))
				{
					if (placeShipsRecursively(b, placedNumShips + 1, totalNumShips, maxRows, maxCols))
						return true;
					b.unplaceShip(Point(r, c), i, HORIZONTAL);	
				}
				  // try vertical
				if (b.placeShip(Point(r, c), i, VERTICAL))
				{
					if (placeShipsRecursively(b, placedNumShips + 1, totalNumShips, maxRows, maxCols))
						return true;
					b.unplaceShip(Point(r, c), i, VERTICAL);	
				}				
			}

	return false;
}


Point GoodPlayer::recommendAttack()
{
	cout << direction << endl;
	const int nRows = game().rows(), nCols = game().cols();
	int r, c;
	if (direction == 0)  // if in state 1, randomly pick blocks by m_step
	{
		while (true)
		{
			r = randInt(nRows); c = randInt(nCols);
			if ((r + c) % m_step == 0 && hitMap[r][c] == '.')
				return Point(r, c);
		}
	}
	else  // if in state 2
	{	
		Point curr_center = centerPoints.back();
		switch(direction)
		{
			case 1 : r = curr_center.r - stepLength;  // NORTH
					 c = curr_center.c;
					 break;
			case 2 : r = curr_center.r + stepLength;  // SOUTH
					 c = curr_center.c;
					 break;
			case 3 : r = curr_center.r;               // WEST
					 c = curr_center.c - stepLength;
					 break;
			case 4 : r = curr_center.r;               // EAST
					 c = curr_center.c + stepLength;
					 break;
		}

		if (r < 0 || r >= nRows || c < 0 || c >= nCols || hitMap[r][c] != '.')  // if not a valid choice, switch direction
		{
			direction--;
			if (direction == 0)
			{
				centerPoints.pop_back();
				stepLength = 1;
				if (centerPoints.empty())
					direction = 0;
				else
					direction = 4;
			}

			return recommendAttack();
		}
		return Point(r, c);
	}

}

void GoodPlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{
	if (validShot)
	{
		hitMap[p.r][p.c] = 'X';  // update hitMap and hitPoints
		if (shotHit)
			hitPoints.push_back(p);
		if (shipDestroyed)  // switch to state 1?
		{
			stepLength = 1;
			centerPoints.clear();
			  // try to find the points that are not in the line of the ship
			vector<Point> temp;
			if (direction < 3)  // NORTH or SOUTH
			{
				for (int i = 0; i < hitPoints.size(); i++)  // record points that are not in the line of the destroyed ship
					if (hitPoints[i].c != p.c)
						temp.push_back(hitPoints[i]);
				if (temp.empty())  // if empty, record head and tail
				{
					Point head(game().rows(), p.c), tail(-1, p.c);
					for (int i = 0; i < hitPoints.size(); i++)
					{
						if (hitPoints[i].r < head.r)
							head = hitPoints[i];
						if (hitPoints[i].r > tail.r)
							tail = hitPoints[i];
					}
					temp.push_back(head); temp.push_back(head);
				}
			}
			else  // WEST or EAST
			{
				for (int i = 0; i < hitPoints.size(); i++)  // record points that are not in the line of the destroyed ship
					if (hitPoints[i].r != p.r)
						temp.push_back(hitPoints[i]);
				if (temp.empty())  // if empty, record head and tail
				{
					Point head(p.r, game().cols()), tail(p.r, -1);
					for (int i = 0; i < hitPoints.size(); i++)
					{
						if (hitPoints[i].c < head.c)
							head = hitPoints[i];
						if (hitPoints[i].c > tail.c)
							tail = hitPoints[i];
					}
					temp.push_back(head); temp.push_back(head);
				}
			}
			if (hitPoints.size() > game().shipLength(shipId))
			{
				centerPoints.swap(temp);
				direction = 4;      // reset direction to 4 and clear hit points
			}
			else
				direction = 0;     // else back to state 1
			hitPoints.clear();

			shipsOfOpponent[shipId] = -1;
			if (game().shipLength(shipId) == m_step)  // need update the minLength?
			{
				m_step = game().rows();
				for (int i = 0; i < shipsOfOpponent.size(); i++)
					if (shipsOfOpponent[i] != -1 && shipsOfOpponent[i] < m_step)
						m_step = shipsOfOpponent[i];
			}
		}
		else if (shotHit && direction == 0)  // if hit a ship and it's in state 1
		{
			centerPoints.clear();
			centerPoints.push_back(p);
			direction = 4;
		}
		else if (!shotHit && direction > 0)
		{
			if (stepLength > 1)  // hit before, search in opposite direction
			{
				if (direction < 3)
					direction = 3 - direction;
				else
					direction = 7 - direction;
				stepLength = 1;
			}
			else
				direction--;
		}
		else if (shotHit && direction > 0)
		{
			stepLength++;
		}
	}
}

void GoodPlayer::recordAttackByOpponent(Point p)
{}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0]) && type != types[pos]; pos++);

    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
