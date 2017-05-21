#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>

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
};

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
	: Player(nm, g)
{}

MediocrePlayer::~MediocrePlayer()
{}

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
	return Point(0, 0);
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot, bool shotHit, bool shipDestroyed, int shipId)
{}

void MediocrePlayer::recordAttackByOpponent(Point p)
{}  // MediocrePlayer ignores opponent's attach

// Remember that Mediocre::placeShips(Board& b) must start by calling
// b.block(), and must call b.unblock() just before returning.

//*********************************************************************
//  GoodPlayer
//*********************************************************************

// TODO:  You need to replace this with a real class declaration and
//        implementation.
typedef AwfulPlayer GoodPlayer;

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
