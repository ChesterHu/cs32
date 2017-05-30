void removeBad(list<Movie*>& li)
{
	list<Movie*>::iterator iter = li.begin();
	Movie* p;
	while (iter != li.end())
	{
		if ((*iter)->rating() < 50)
		{
			p = *iter;
			iter = li.erase(iter);
			delete p;
		}
		else
		{
			iter++;
		}
	}
}
