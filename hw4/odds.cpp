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
