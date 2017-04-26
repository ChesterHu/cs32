#include <iostream>
using namespace std;

int main()
{
  char a;;
  if ((a = '\0'))
  {
    cout << "null byte -> true" << endl;
  }
  else
  {
    cout << "null byte -> false" << endl;
  }

  return 0;
}
