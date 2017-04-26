#include <iostream>
using namespace std;

int main()
{
  int* ptr = new int(1);
  int* a;
  delete ptr;
  if (!ptr)
  {
    cout <<  "ptr is nullptr now" << endl;
  }
  else
  {
    cout << "ptr is a dangling pointer, point to unknown address and we can't access the data in it." << endl;
  }

  return 0;
}
