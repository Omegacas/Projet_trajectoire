#include<cmath>
#include <iostream>
#include <vector>
#include "../include/trajectoire.hpp"

using namespace std ; 

template <typename T>
graph conv_spatial_graph(vector<vector<T>> obstacle)
{
    int n = obstacle.size();
    graph obs;
    arc a;
    for(int i = 0; i<n ;i++)
    {
        arc.sommet1 = obstacle[i];
        arc.sommet2 = obstacle[(i+1)%n];
    }
    return;
}