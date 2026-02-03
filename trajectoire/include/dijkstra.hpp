#include<cmath>
#include <iostream>
#include <vector>
#include <map>



vector<vector<double>> dijkstra(vector<vector<double>> matrice_graphe, vector<double> depart, vector<double> arrivee) {
    int n = matrice_graphe.size();
    vector<double> tableau(n);
    vector<double> parcours;
    vector<double> etape = depart;

    // Initialisation de tableau
    for(int i =0; i<n; ++i){
        if matrice(depart)(i) == 0{
            tableau(i) = 999999;}// A remplacer par + infini pour la prochaine fois
        else{
            tableau(i) = matrice(depart)(i);
        }
        tableau(depart)(depart) = 0;

    //Iteration
    parcours.push_back(etape);
    
    



        
        
    }




    
}
// retourne un vecteur avec les sommets parcourus