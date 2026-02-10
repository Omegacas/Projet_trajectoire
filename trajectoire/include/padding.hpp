#include<cmath>
#include <iostream>
#include <vector>
#include <map>

class obstacle_padded
{
    protected:
    double rayon ;
    vector<vector<double>> sommets; //sommets dans le sens trigo
    vector<vector<double>> normales; //normales des sommets Si(Si+1)
    int nbsommets;
    public :
    obstacle (const vector<vector<double>>& u): sommets(u)
    {
        nbsommets = sommets.size();
        for (int i = 0; i<nbsommets; ++i)
        {
            vector<double> v = sommets[i];
            vector<double> w = sommets [(i+1)%nbsommets]; //si i+1=n, on retombe au sommet 0
            vector<double> arete = w-v;
            normales[i][0] = -arete[1];
            normales[i][1] = arete[0];
        }
    }
    virtual void print(ostream& out) const
    {
        for (int i = 0; i<nbsommets; ++i)
        {
            out << sommets[i];
            out
        }
    }
}