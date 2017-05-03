// #include "mazestack.cpp"
#include <iostream>
#include "mazequeue.cpp"
#include "eval.cpp"
#include <cassert> // for testing
using namespace std;

bool test(int sr, int sc, int er, int ec) {
  char maze[10][10] = {{'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
                       {'X', '.', '.', '.', '.', '.', '.', '.', '.', 'X'},
                       {'X', 'X', '.', 'X', '.', 'X', 'X', 'X', 'X', 'X'},
                       {'X', '.', '.', 'X', '.', 'X', '.', '.', '.', 'X'},
                       {'X', '.', '.', 'X', '.', '.', '.', 'X', '.', 'X'},
                       {'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', '.', 'X'},
                       {'X', '.', 'X', '.', '.', '.', '.', 'X', 'X', 'X'},
                       {'X', '.', 'X', 'X', 'X', '.', 'X', 'X', '.', 'X'},
                       {'X', '.', '.', '.', 'X', '.', '.', '.', '.', 'X'},
                       {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'}};

  return pathExists(maze, sr, sc, er, ec);
}

void test_eval() {
  do {
    assert(!lessEqual('&', '|'));
    assert(lessEqual('&', '&'));
    assert(lessEqual('&', '!'));
    bool x;
    assert(postfixEval("TF&", x) && !x);
    assert(!postfixEval("TF&|", x) && !x);
    assert(postfixEval("T!T|", x) && x);
    assert(postfixEval("FF!TF&&|", x) && !x);
    assert(postfixEval("TF|", x) && x);
    assert(postfixEval("T", x) && x);
    assert(postfixEval("F", x) && !x);
  } while (0);

  do {
    string pf;
    bool answer;
    assert(evaluate(" T | F", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate("T| ", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("T F", pf, answer) == 1);
    assert(evaluate("   (        )", pf, answer) == 1);
    assert(evaluate("T(  F|  T)", pf, answer) == 1);
    assert(evaluate("T(& T)", pf, answer) == 1);
    assert(evaluate("(T&  (F  |F)", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&|" &&
           !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("(  (T )  )", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("F T(  F  )", pf, answer) == 1 && answer);
    assert(evaluate("T", pf, answer) == 0 && answer);
    assert(evaluate("(   F   )", pf, answer) == 0 && !answer);
    assert(evaluate("T&(F)", pf, answer) == 0 && pf == "TF&" && !answer);
    assert(evaluate("T & !F", pf, answer) == 0 && answer);
    assert(evaluate("!(F|T)", pf, answer) == 0 && !answer);
    assert(evaluate("!F|T", pf, answer) == 0 && pf == "F!T|" && answer);
    assert(evaluate(" T   |F&F", pf, answer) == 0 && pf == "TFF&|" && answer);
    assert(evaluate("F()", pf, answer) == 1);
    assert(evaluate(" )", pf, answer) == 1);
    assert(evaluate("( T (F   ))", pf, answer) == 1);
    assert(evaluate("( T &  T  |  F)&T", pf, answer) == 0 && pf == "TT&F|T&" &&
           answer);
    assert(evaluate("(T &)(F)", pf, answer) == 1);
    assert(evaluate("T|F &F", pf, answer) == 0 && answer);
    assert(evaluate("T&!( F|T&T|F  )  |  !  !  ! (F&T&F)  ", pf, answer) == 0 &&
           answer);
    assert(evaluate("  F   !    ", pf, answer) == 1);
    assert(evaluate("!F", pf, answer) == 0 && answer);
    assert(evaluate("dsvfwe rg", pf, answer) == 1 && answer);
    assert(evaluate("TF&", pf, answer) == 1 && answer);
    assert(evaluate("  T   T   &   ", pf, answer) == 1 && answer);
  } while (0);
}

int main() {
  assert(test(6, 4, 1, 1));
  assert(test(8, 8, 1, 1));
  assert(test(7, 8, 1, 1));
  assert(!test(8, 1, 1, 1));
  assert(test(6, 3, 1, 1));
  assert(!test(8, 3, 1, 1));
  test_eval();
  std::cout << "Passed all test" << endl;
  return 0;
}
