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
	b.display(false);
    if (helper(b, 0, game().nShips(), game().rows(), game().cols()))
    {
      b.unblock();    // call unblock function
      return true;
    }
    b.unblock();
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
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
    bool helper(Board& b, int placedNumShips, int totalNumShips, int rows, int cols);
  private:
    bool m_state;
    char** hitBefore;
    Point m_lastCellAttacked;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
 : Player(nm, g)
{
  m_state = false;
  m_lastCellAttacked = Point(0,0);
  hitBefore = new char* [game().rows()];
  for (int i=0; i<game().rows(); i++) 
  {
    hitBefore[i] = new char [game().cols()];
    for (int j=0; j<game().cols(); j++) 
    {
      hitBefore[i][j] = '.';
    }
  }
}

GoodPlayer::~GoodPlayer()
{
  for (int i=0; i<game().rows(); i++)
    delete [] hitBefore[i];
  delete [] hitBefore;
}

bool GoodPlayer::placeShips(Board& b)
{
  

  for (int i = 0; i < 50; i++)  // try 50 times to place ship
  {
    b.block();  // call the block function
    if (helper(b, 0, game().nShips(), game().rows(), game().cols()))
    {
      b.unblock();    // call unblock function
      return true;
    }
    b.unblock();
  }

  return false;
}

bool GoodPlayer::helper(Board& b, int placedNumShips, int totalNumShips, int rows, int cols)
{
  if (placedNumShips == totalNumShips)
    return true;
    // try place ships
  for (int i = 0; i < totalNumShips; i++)
    for (int c = 0; c < cols; c++)
      for(int r = 0; r < rows; r++)
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

Point GoodPlayer::recommendAttack()
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

void GoodPlayer::recordAttackResult(Point p, bool validShot,
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


void GoodPlayer::recordAttackByOpponent(Point /* p */)
{
      // GoodPlayer completely ignores what the opponent does
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
