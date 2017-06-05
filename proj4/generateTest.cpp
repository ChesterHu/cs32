#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
using namespace std;

const double PROB_SCOPECHANGE = 0.10;
const double ENTER_BIAS = 0.54;
const double PROB_DECLARE_VS_USE = 0.20;
const double PROB_UNDECLARED = 0.01;
const double PROB_DUPDECLARE = 0.01;
const double PROB_DEFAULT_ID_LEN = 0.90;
const int DEFAULT_ID_LEN = 6;
const int MAX_ID_LEN = 20;

random_device aRandomDevice;
mt19937 generator(aRandomDevice());

bool trueWithProb(double p)
{
    uniform_real_distribution<> distro(0, 1);
    return distro(generator) < p;
}

int randInt(int n)
{
    uniform_int_distribution<> distro(0, n-1);
    return distro(generator);
}

int main()
{
    cout << "Enter output file name: ";
    string filename;
    getline(cin,filename);
    cout << "About how many test file lines should I generate? ";
    int nlines;
    cin >> nlines;
    ofstream outf(filename.c_str());
    if (!outf)
    {
        cout << "Cannot create " << filename << endl;
        return 1;
    }

    int nestingLevel = 0;
    vector<string> ids;
    for (int n = 1; n <= nlines; n++)
    {
        if (trueWithProb(PROB_SCOPECHANGE))
        {
            if (nestingLevel > 0  &&
                     trueWithProb(n < nlines / 2 ? (1-ENTER_BIAS) : ENTER_BIAS))
            {
                outf << "}\n";
                nestingLevel--;
            }
            else
            {
                outf << "{\n";
                nestingLevel++;
            }
        }
        else if (trueWithProb(PROB_DECLARE_VS_USE)  ||  ids.empty())
        {
            static char name[MAX_ID_LEN+1];
            int len = DEFAULT_ID_LEN;
            if (!trueWithProb(PROB_DEFAULT_ID_LEN))
                len = 1 + randInt(MAX_ID_LEN);
            for (int k = 0; k < len; k++)
            {
                int r = randInt(2*26);
                name[k] = (r < 26 ? 'a'+r : 'A'+r-26);
            }
            name[len] = '\0';
            ids.push_back(name);
            outf << name;
            if (!trueWithProb(PROB_UNDECLARED))
                outf << ' ' << n;
            outf << endl;
        }
        else if (trueWithProb(PROB_DUPDECLARE))
            outf << ids[randInt(ids.size())] << ' ' << n << endl;
        else
            outf << ids[randInt(ids.size())] << endl;
    }
    for ( ; nestingLevel > 0; nestingLevel--)
        outf << "}\n";
}
