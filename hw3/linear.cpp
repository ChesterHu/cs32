#include <string>
#include <iostream>
#include <cassert>
using namespace std;
bool somePredicate(string s)
{
	return !s.empty();
}

bool allTrue(const string a[], int n);
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise

int countFalse(const string a[], int n);
// Return the number of elements in the array for which the
// somePredicate function returns false

int firstFalse(const string a[], int n);
// Return the subscript of the first element in the array for which
// the somePredicate function returns false. If there is no such
// elements, return -1.

int indexOfLeast(const string a[], int n);
// Return the subscript of the least string in the array (i.e., 
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1). If the array has no elements to examine,
// return -1.

bool includes(const string a1[], int n1, const string a2[], int n2);
// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then return
// true; otherwise (i.e. if the array a1 does not include a2 as a not-
// necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "martman"
// and it should return false if as is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

int main()
{
	string m_array[] = { "abc", "", "ad", "", "dd"};
	assert(!allTrue(m_array, 5));
	assert(countFalse(m_array, 5) == 2);
	assert(firstFalse(m_array, 5) == 1);
	assert(indexOfLeast(m_array, 5) == 3);

	do {
		string a1[] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
		string a2[] = {"stan", "kenny", "cartman"};
		string a3[] = {"stan", "cartman", "butters"};
		string a4[] = {"kyle", "cartman", "cartman"};
		string a5[] = {"kyle", "butters", "kenny"};
		string a6[] = {"stan", "kenny", "kenny"};
		assert(includes(a1, 7, a2, 3));
		assert(includes(a1, 7, a3, 3));
		assert(includes(a1, 7, a4, 3));
		assert(!includes(a1, 7, a5, 3));
		assert(!includes(a1, 7, a6, 3));
	} while (0);
	cout << "Passed all tests" << endl;
}

// function implementation
///////////////////////////////////////////////////////////
bool allTrue(const string a[], int n)
{
	if (n < 1) return true;
	if (!somePredicate(a[n - 1]))
		return false;
	return allTrue(a, n - 1);
}

int countFalse(const string a[], int n)
{
	if (n < 1) return 0;
	return (somePredicate(a[n - 1])) ? countFalse(a, n - 1) : 1 + countFalse(a, n - 1);
}

int firstFalse(const string a[], int n)
{
	if (n < 1) return -1;
	if (!somePredicate(a[n - 1]))
	{
		int next_idx = firstFalse(a, n - 1);
		if (next_idx == -1)   // it's the first false
			return n - 1;
		return next_idx;
	}
	return firstFalse(a, n - 1);
}

int indexOfLeast(const string a[], int n)
{
	if (n < 1) return -1;
	int next_idx = indexOfLeast(a, n - 1);   // return the next possible small index
	if (next_idx == -1)
		return n - 1;
	return (a[next_idx] < a[n - 1]) ? next_idx : n - 1;
}

bool includes(const string a1[], int n1, const string a2[], int n2)   // duplicates in a2?
{
	if (n2 < 1) return true;    // if a2 is empty, then all of elements can be found in a1
	if (n1 < n2 || n1 < 1) return false;  // situations a1 can't includes a2

	if (a1[n1 - 1] == a2[n2 - 1])
		return includes(a1, n1 - 1, a2, n2 - 1);
	else
		return includes(a1, n1 - 1, a2, n2);
}
