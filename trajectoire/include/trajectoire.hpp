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

vector<double> operator*(const double& s, const vector<double>& u) {
    vector<double> w = u;
    for (auto& wi : w) wi *= s;
    return w;
}

vector<double> operator*(const vector<double>& u, const double& s) {
    return s * u;
}


// classe obstacle
class obstacle
{
    protected:
    vector<vector<double>> sommets; //sommets dans le sens trigo
    vector<vector<double>> aretes; //vecteurs orientés dans le sens trigo
    vector<vector<double>> normales; //normales des sommets SiSi+1
    int nbsommets;
    public :
    obstacle (const vector<vector<double>>& u): sommets(u)
    {
        nbsommets = sommets.size();
        for (int i = 0; i<nbsommets; ++i)
        {
            vector<double> v = sommets[i];
            vector<double> w = sommets [(i+1)%nbsommets]; //si i+1=nbsommets, on retombe au sommet 0
            aretes[i] = w-v;
            normales[i][0] = -aretes[i][1];
            normales[i][1] = aretes[i][0];
        }
    }
    virtual ~obstacle(){};
    virtual void print(ostream& out) const
    {
        for (int i = 0; i<nbsommets; ++i)
        {
            out << sommets[i];
        }
    }
    virtual vector<double> intersection(const double& a, const double& b) //droite y=ax+b
    {
        
    }
};

ostream& operator<<(ostream& os, const obstacle& O) 
{
    O.print(os);
    return os;
}

//penser à réindexer les sommets des obstacles lorsqu'on les mettra tous dans un seul graphe