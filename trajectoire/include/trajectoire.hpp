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
    virtual vector<double> intersection(const double& a, const double& b) //droite y=ax+b (traiter aussi le cas d'une droite verticale)
    {
        for (int i = 0; i<nbsommets; ++i) //boucle sur les côtés de l'obstacle
        {
            vector<double> arete = aretes[i];
            vector<double> s = sommets[i];
            //on suppose ici que aretes[i][0]!=0 (cas =0 à traiter avec un if)
            double pente_arete = arete[1]/arete[0];
            double ord = s[1] - pente_arete*s[0]; //calcul de l'ordonnée à l'origine de la droite de l'arete
            if (abs(pente_arete - a)<1e-5) //teste si le côté et la droite ont la même pente
            {
                if (abs(ord-b)<1e-5)// teste si même ordonnée à l'origine 
                {
                    return s;
                }
            }
            else //il y a nécessairement un unique pt d'intersection entre la droite et le côté qu'on a prolongé en une droite
            {
                vector<double> point_intersection;
                point_intersection[0] = (b-ord)/(pente_arete - a); //formule de cramer pour résoudre le système 2x2
                point_intersection[1] = (b*pente_arete-a*ord)/(pente_arete - a);
                if (sommets[i][1]<point_intersection[1] && sommets[i+1][1]>point_intersection[1]) //on vérifie que le point d'intersection est sur le côté
                {
                    return point_intersection;
                }
            }
        }
        return {};
    }
};

ostream& operator<<(ostream& os, const obstacle& O) 
{
    O.print(os);
    return os;
}

//penser à réindexer les sommets des obstacles lorsqu'on les mettra tous dans un seul graphe