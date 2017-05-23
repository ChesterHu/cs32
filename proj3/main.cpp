#include "Game.h"
#include "Player.h"
#include "Board.h"
#include <iostream>
#include <string>

using namespace std;

bool addStandardShips(Game& g)
{
    return g.addShip(5, 'A', "aircraft carrier")  &&
           g.addShip(4, 'B', "battleship")  &&
           g.addShip(3, 'D', "destroyer")  &&
           g.addShip(3, 'S', "submarine")  &&
           g.addShip(2, 'P', "patrol boat");
}

void test()
{
	do {
		Game g(10, 10);
		assert(addStandardShips(g));
		assert(g.nShips() == 5);
		assert(g.rows() == 10 && g.cols() == 10);
		assert(g.shipLength(0) == 5 && g.shipLength(4) == 2);
		assert(g.shipSymbol(2) == 'D' && g.shipSymbol(3) == 'S');
		assert(g.shipName(1) == "battleship" && g.shipName(0) == "aircraft carrier");
          // test placeShip() and unplaceShip()
		Board b(g);
		b.clear();
		b.block();
		b.unblock();
		assert(b.placeShip(Point(0, 0), 0, HORIZONTAL));
		assert(b.unplaceShip(Point(0, 0), 0, HORIZONTAL));
		assert(b.placeShip(Point(1, 1), 0, VERTICAL));
		assert(!b.unplaceShip(Point(2, 1), 0, VERTICAL));
		assert(b.unplaceShip(Point(1, 1), 0, VERTICAL));
		assert(b.placeShip(Point(0, 0), 0, HORIZONTAL));
		assert(b.placeShip(Point(1, 1), 1, VERTICAL));
		assert(!b.placeShip(Point(2, 2), 1, VERTICAL));
		assert(!b.placeShip(Point(1, 0), 4, HORIZONTAL));
		assert(b.placeShip(Point(1, 2), 4, HORIZONTAL));
		// b.display(true);
		// b.display(false);
        
        int shipId = 1;
        bool shotHit = true, shipDestroyed = true;
        assert(!b.attack(Point(-1, 0), shotHit, shipDestroyed, shipId) && !b.attack(Point(10, 1), shotHit, shipDestroyed, shipId));
        assert(b.attack(Point(1, 0), shotHit, shipDestroyed, shipId) && !shotHit && !shipDestroyed && shipId == 1);
        assert(b.attack(Point(0, 0), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 0);  
        assert(b.attack(Point(0, 1), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 0);  
        assert(b.attack(Point(0, 2), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 0);  
        assert(b.attack(Point(1, 1), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 1);  
        assert(b.attack(Point(0, 3), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 0);  
        assert(b.attack(Point(0, 4), shotHit, shipDestroyed, shipId) && shotHit && shipDestroyed && shipId == 0);  
        assert(b.attack(Point(2, 1), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 1);  
        assert(b.attack(Point(1, 2), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 4);  
        assert(b.attack(Point(3, 1), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 1);
        assert(!b.allShipsDestroyed()); 
        assert(b.attack(Point(4, 1), shotHit, shipDestroyed, shipId) && shotHit && shipDestroyed && shipId == 1);  
        assert(b.attack(Point(1, 3), shotHit, shipDestroyed, shipId) && shotHit && shipDestroyed && shipId == 4);
        assert(b.allShipsDestroyed());
	} while (0);

	do {
		  // second test
		Game g(10, 10);
		assert(addStandardShips(g));
		Board b(g);
		b.clear();
		assert(b.placeShip(Point(0, 0), 4, HORIZONTAL));
		
		bool shotHit = true, shipDestroyed = true;
		int shipId = 0;
		assert(b.attack(Point(1, 1), shotHit, shipDestroyed, shipId) && !shotHit && !shipDestroyed && shipId == 0);
		assert(!b.allShipsDestroyed());
		assert(b.attack(Point(0, 0), shotHit, shipDestroyed, shipId) && shotHit && !shipDestroyed && shipId == 4);
		// b.display(true);
		// b.display(false);
		assert(b.attack(Point(0, 1), shotHit, shipDestroyed, shipId) && shotHit && shipDestroyed && shipId == 4);
		// b.display(false);
		assert(b.allShipsDestroyed());
	} while(0);

	do {
		  // third test
		Game g(10, 10);
		addStandardShips(g);
		Player* p1 = createPlayer("human", "chufeng", g);
		Player* p2 = createPlayer("good", "a", g);
		assert(g.play(p1, p2) == p1);
		delete p1;
		delete p2;
	} while (0);
	
	do {
		Game g(10, 10);
		addStandardShips(g);
		Player* p1 = createPlayer("mediocre", "a", g);
		Board b(g);
		b.clear();
		p1->placeShips(b);
		b.display(false);
		delete p1;
	} while (0);

	cout << "Passed all tests" << endl;
}


int main()
{
    const int NTRIALS = 10;
	test();
	/*
    cout << "Select one of these choices for an example of the game:" << endl;
    cout << "  1.  A mini-game between two mediocre players" << endl;
    cout << "  2.  A mediocre player against a human player" << endl;
    cout << "  3.  A " << NTRIALS
         << "-game match between a mediocre and an awful player, with no pauses"
         << endl;
    cout << "Enter your choice: ";
    string line;
    getline(cin,line);
    if (line.empty())
    {
        cout << "You did not enter a choice" << endl;
    }
    else if (line[0] == '1')
    {
        Game g(2, 3);
        g.addShip(2, 'R', "rowboat");
        Player* p1 = createPlayer("mediocre", "Popeye", g);
        Player* p2 = createPlayer("mediocre", "Bluto", g);
        cout << "This mini-game has one ship, a 2-segment rowboat." << endl;
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '2')
    {
        Game g(10, 10);
        addStandardShips(g);
        Player* p1 = createPlayer("mediocre", "Mediocre Midori", g);
        Player* p2 = createPlayer("human", "Shuman the Human", g);
        g.play(p1, p2);
        delete p1;
        delete p2;
    }
    else if (line[0] == '3')
    {
        int nMediocreWins = 0;

        for (int k = 1; k <= NTRIALS; k++)
        {
            cout << "============================= Game " << k
                 << " =============================" << endl;
            Game g(10, 10);
            addStandardShips(g);
            Player* p1 = createPlayer("awful", "Awful Audrey", g);
            Player* p2 = createPlayer("mediocre", "Mediocre Mimi", g);
            Player* winner = (k % 2 == 1 ?
                                g.play(p1, p2, false) : g.play(p2, p1, false));
            if (winner == p2)
                nMediocreWins++;
            delete p1;
            delete p2;
        }
        cout << "The mediocre player won " << nMediocreWins << " out of "
             << NTRIALS << " games." << endl;
          // We'd expect a mediocre player to win most of the games against
          // an awful player.  Similarly, a good player should outperform
          // a mediocre player.
    }
    else
    {
       cout << "That's not one of the choices." << endl;
    }
	*/
}
