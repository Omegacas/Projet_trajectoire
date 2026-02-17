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

vector<double> operator*(const double& s, const vector<double>& u) 
{
    vector<double> w = u;
    for (auto& wi : w) wi *= s;
    return w;
}

vector<double> operator*(const vector<double>& u, const double& s) 
{
    return s * u;
}

double operator|(const vector<double>& u, const vector<double>& v)
{
    double ps = 0;
    int n = min(u.size(), v.size());
    for (int i = 0;i<n;i++)
    {
        ps += u[i]*v[i];
    }
    return ps;
}

double norme2(const vector<double>& u) 
{
    return sqrt(u | u);
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
    virtual vector<double> intersection(const vector<double>& a, const vector<double>& v)
    {
        for (int i = 0; i<nbsommets; ++i) //boucle sur les côtés de l'obstacle
        {
            vector<double> arete = aretes[i];
            vector<double> s = sommets[i];
            if ((v[0]*arete[1]-v[1]*arete[0])<1e-5) //vecteurs directeurs de la droite et de l'arete colinéaires 
            {
                vector<double> w = s-a;
                if ((v[0]*w[1]-v[1]*w[0])<1e-5) //teste si droite superposée avec l'arête
                {
                    return s; // s est un des points d'intersection (il y en a une infinité)
                }
                else
                {
                    return {}; //vecteur vide : pas de pt d'intersection
                }
            }
            else //il y a nécessairement un unique pt d'intersection entre la droite et le côté qu'on a prolongé en une droite
            {
                double t = ((s[0]-a[0])*(-arete[1])+(s[1]-a[1])*arete[0])/(arete[0]*v[1]-arete[1]*v[0]);
                vector<double> inter;
                inter[0] = t*v[0] + a[0];  //pt d'intersection
                inter[1] = t*v[1] + a[1];
                if (sommets[i][1]<inter[1] && sommets[i+1][1]>inter[1]) //on vérifie que le point d'intersection est sur le côté
                    {
                        return inter;
                    }
            }
        }
    }
};

ostream& operator<<(ostream& os, const obstacle& O) 
{
    O.print(os);
    return os;
}

//penser à réindexer les sommets des obstacles lorsqu'on les mettra tous dans un seul graphe

//classe arc

class arc
{
    protected:
    vector<double> sommet1; //coordonnées sommet 1
    vector<double> sommet2; //coordonnées sommet 2
    int num1;  //numérotation sommet 1
    int num2;  //numérotation sommet 2
    double poids; //poids de l'arc
};

class graph : public arc
{
    protected:
    vector<arc> arcs;
    vector<vector<double>> matrice_adj;
    int nb_arcs;
    public:
    graph (const vector<arc>& u) : arcs(u)
    {
        nb_arcs=arcs.size();
        for (int i=0;i<nb_arcs;++i)
        {
            if (poids < 1e-5)
            {
                arcs.erase(arcs.begin()+i);
                matrice_adj[num1][num2] = 0;
            }
            else
            {
                matrice_adj[num1][num2] = poids;
            }
        }
    }
};

class scene : public arc
{
    protected:
    vector<double> depart;
    vector<double> arrivee;
    vector<arc> arcs;
    vector<int> solution;
    scene (const vector<arc>& u, ) : arcs(u)
}