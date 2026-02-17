#include<cmath>
#include <iostream>
#include <vector>
#include <map>
#include "dijkstra.hpp"

using namespace std;

//outils vecteurs
template <typename T>
ostream& operator<<(ostream& os ,const vector<T>& v)
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

template <typename T>
vector<T> operator+(const vector<T>& u, const vector<T>& v)
{
    int n=u.size();
    vector<T> w(n);
    for (int i=0;i<n; i++) 
    {
        w[i]=u[i]+v[i];
    }
    return w;
}

template <typename T>
vector<T> operator-(const vector<T>& u, const vector<T>& v)
{
    int n=u.size();
    vector<T> w(n);
    for (int i=0;i<n; i++) 
    {
        w[i]=u[i]-v[i];
    }
    return w;
}

template <typename T>
vector<T> operator*(const T& s, const vector<T>& u) 
{
    vector<T> w = u;
    for (auto& wi : w) wi *= s;
    return w;
}

template <typename T>
vector<T> operator*(const vector<T>& u, const T& s) 
{
    return s * u;
}

template <typename T>
T operator|(const vector<T>& u, const vector<T>& v)
{
    T ps = 0;
    int n = min(u.size(), v.size());
    for (int i = 0;i<n;i++)
    {
        ps += u[i]*v[i];
    }
    return ps;
}

template <typename T>
T norme2(const vector<T>& u) 
{
    return sqrt(u | u);
}

template <typename T>
class obstacle
{
    protected:
    vector<vector<T>> sommets; 
    vector<vector<T>> aretes; 
    vector<vector<T>> normales; 
    int nbsommets;
    public :
    obstacle (const vector<vector<T>>& u): sommets(u)
    {
        nbsommets = sommets.size();
        aretes.resize(nbsommets);
        normales.assign(nbsommets, vector<T>(2));
        for (int i = 0; i<nbsommets; ++i)
        {
            vector<T> v = sommets[i];
            vector<T> w = sommets [(i+1)%nbsommets];
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
    virtual vector<T> intersection(const vector<T>& a, const vector<T>& v)
    {
        for (int i = 0; i<nbsommets; ++i)
        {
            vector<T> arete = aretes[i];
            vector<T> s = sommets[i];
            if (abs(v[0]*arete[1]-v[1]*arete[0]) < 1e-5) 
            {
                vector<T> w = s-a;
                if (abs(v[0]*w[1]-v[1]*w[0]) < 1e-5) 
                {
                    return s; 
                }
                else
                {
                    return {}; 
                }
            }
            else 
            {
                T t = ((s[0]-a[0])*(-arete[1])+(s[1]-a[1])*arete[0])/(arete[0]*v[1]-arete[1]*v[0]);
                vector<T> inter(2);
                inter[0] = t*v[0] + a[0]; 
                inter[1] = t*v[1] + a[1];
                if (sommets[i][1]<inter[1] && sommets[(i+1)%nbsommets][1]>inter[1]) 
                {
                    return inter;
                }
            }
        }
        return {};
    }
};

template <typename T>
ostream& operator<<(ostream& os, const obstacle<T>& O) 
{
    O.print(os);
    return os;
}

template <typename T>
class arc
{
    public:
    vector<T> sommet1; 
    vector<T> sommet2; 
    int num1;  
    int num2;  
    T poids; 
};

template <typename T>
class graph
{
    protected:
    vector<arc<T>> arcs;
    vector<vector<T>> matrice_adj;
    int nb_arcs;
    public:
    graph (const vector<arc<T>>& u, int n) : arcs(u)
    {
        nb_arcs=arcs.size();
        matrice_adj.assign(n, vector<T>(n, 0));
        for (int i=0; i<nb_arcs; ++i)
        {
            if (arcs[i].poids >= 1e-5)
            {
                matrice_adj[arcs[i].num1][arcs[i].num2] = arcs[i].poids;
            }
        }
    }
};

template <typename T>
class scene : public graph<T>
{
    protected:
    vector<T> depart;
    vector<T> arrivee;
    vector<int> solution;
    public:
    scene (const vector<arc<T>>& u, vector<T> a, vector<T> b, int n, int id1, int id2) : graph<T>(u, n), depart(a), arrivee(b)
    {
        solution = dijkstra(this->matrice_adj, id1, id2); // id1 et id2 numéros de sommets départ et arrivée
    }
};