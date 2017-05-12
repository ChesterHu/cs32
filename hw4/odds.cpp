#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

	// Remove the odd integers from v.
	// It is acceptable if the order of the remaining even integers is not
	// the same as in the original vector.
void removeOdds(vector<int>& v);

void test()
{
	int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	vector<int> x(a, a+8);  // construct x from the array
	assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	removeOdds(x);
	assert(x.size() == 4);
	sort(x.begin(), x.end());
	int expect[4] = { 2, 4, 6, 8 };
	for (int k = 0; k < 4; k++)
		assert(x[k] == expect[k]);
}

int main()
{
		test();
		cout << "Passed" << endl;
}

void removeOdds(vector<int>& v)
{
	// first move all odds elements to the tail of vector
	// the oddsStart records start position of odds integer
	// then erase all elements start by oddsStart.

	int oddsStart = v.size();
	int unknown = 0;
	int temp = 0;
	while (unknown < oddsStart)
	{
		if (v[unknown] % 2 == 1)
		{
			temp = v[unknown];
			v[unknown] = v[oddsStart - 1];
			v[oddsStart] = temp;
			oddsStart--;
		}
		else
			unknown++;
	}

	v.erase(v.begin() + oddsStart, v.end());
}
