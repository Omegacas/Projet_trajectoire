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

// classe obstacle
template <typename T>
class obstacle
{
    protected:
    vector<vector<T>> sommets; //sommets dans le sens trigo
    vector<vector<T>> aretes; //vecteurs orientés dans le sens trigo
    vector<vector<T>> normales; //normales des sommets SiSi+1
    int nbsommets;
    public :
    obstacle (const vector<vector<T>>& u): sommets(u)
    {
        nbsommets = sommets.size();
        for (int i = 0; i<nbsommets; ++i)
        {
            vector<T> v = sommets[i];
            vector<T> w = sommets [(i+1)%nbsommets]; //si i+1=nbsommets, on retombe au sommet 0
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
        for (int i = 0; i<nbsommets; ++i) //boucle sur les côtés de l'obstacle
        {
            vector<T> arete = aretes[i];
            vector<T> s = sommets[i];
            if ((v[0]*arete[1]-v[1]*arete[0])<1e-5) //vecteurs directeurs de la droite et de l'arete colinéaires 
            {
                vector<T> w = s-a;
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
                T t = ((s[0]-a[0])*(-arete[1])+(s[1]-a[1])*arete[0])/(arete[0]*v[1]-arete[1]*v[0]);
                vector<T> inter;
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

template <typename T>
ostream& operator<<(ostream& os, const obstacle<T>& O) 
{
    O.print(os);
    return os;
}

//penser à réindexer les sommets des obstacles lorsqu'on les mettra tous dans un seul graphe

//classe arc

template <typename T>
class arc
{
    protected:
    vector<T> sommet1; //coordonnées sommet 1
    vector<T> sommet2; //coordonnées sommet 2
    int num1;  //numérotation sommet 1
    int num2;  //numérotation sommet 2
    T poids; //poids de l'arc
};

template <typename T>
class graph : public arc<T>
{
    protected:
    vector<T> arcs;
    vector<vector<T>> matrice_adj;
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

template <typename T>
class scene : public graph<T>
{
    protected:
    vector<T> depart;
    vector<T> arrivee;
    vector<arc> arcs;
    vector<vector<T>> matrice_adj;
    vector<T> solution;
    scene (const vector<arc>& u, vector<T> a, vector<T> b, vector<vector<T>> m) : arcs(u), depart(a), arrivee(b), matrice_adj(m)
    {
        solution = dijkstra(matrice_adj, depart, arrivee);
    }
};