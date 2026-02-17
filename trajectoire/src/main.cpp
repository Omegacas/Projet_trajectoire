#include <iostream>
#include <vector>
#include "../include/dijkstra.hpp"
#include "../include/trajectoire.hpp"


using namespace std ;

int main()
{
    //TEST DIJKSTRA
    vector<vector<double>> matrice_graphe = {
    {0,7,9,0,0,14},
    {7,0,10,15,0,0},
    {9,10,0,11,0,2},
    {0,15,11,0,6,0},
    {0,0,0,6,0,9},
    {14,0,2,0,9,0}};
    int depart = 0;
    int arrivee = 5;
    // devrait retourner {1,2,3,6}
    vector<int> chemin  = dijkstra(matrice_graphe, depart, arrivee);
    cout<<chemin<<endl;


}




