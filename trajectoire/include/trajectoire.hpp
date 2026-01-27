#include<cmath>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

//outils vecteurs
ostream& operator<<(ostream& os ,const vector<double>& v)
{
    int n = v.size();
    if (v.empty()) {
            os << "()";
            return os;
        }
    os<<"(" ;
    for (int i = 0; i < n; ++i) 
        {
        os << v[i];
        if (i < n - 1) os << ",";
        }
        os << ")";
    return os ;
}

vector<double> operator+(const vector<double>& u, const vector<double>& v)
{
    int n=u.size();
    vector<double> w(n);
    for (int i=0;i<n; i++) 
    {
        w[i]=u[i]+v[i];
    }
    return w;
}

vector<double> operator-(const vector<double>& u, const vector<double>& v)
{
    int n=u.size();
    vector<double> w(n);
    for (int i=0;i<n; i++) 
    {
        w[i]=u[i]-v[i];
    }
    return w;
}


// classe obstacle
class obstacle
{
    protected:
    vector<vector<double>> sommets; //sommets dans le sens trigo
    vector<vector<double>> normales; //normales des sommets SiSi+1
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
            
        }
    }
}