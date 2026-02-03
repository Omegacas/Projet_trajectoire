#include<cmath>
#include <iostream>
#include <vector>
#include <map>



vector<vector<double>> dijkstra(vector<vector<double>> matrice_graphe, int depart, int arrivee) {
   int n = matrice_graphe.size();

    vector<double> tableau(n);
    vector<int> parcours;
    vector<int> visite(n);
    vector<int> predecesseur(n)
    vector<double> etape = depart;

    if(depart == arrivee){
        return{depart};
    }

    // Initialisation de tableau et visites
    for(int i =0; i<n; ++i){
        visite(i) = 0;
        predecesseur(i) = -1;
        if matrice(depart)(i) == 0{
            tableau(i) = 999999;}// A remplacer par + infini pour la prochaine fois
        else{
            tableau(i) = matrice(depart)(i);
        }
        tableau(depart) = 0;

    //Iteration
    int etape = depart;
    while (etape != -1 && etape != arrivee) {
        visite(etape) = 1;
        parcours.push_back(etape);

        for (int i = 0; i < n; i++) {
            if (matrice_graphe[etape][i] > 0 && visites[i]!=1) {
                double nouvelle_dist = tableau[etape] + matrice_graphe[etape][i];
                if (nouvelle_dist < tableau[i]) {
                    tableau[i] = nouvelle_dist;
                    predecesseur[i] = etape;
                }
            }
        }

        // Trouver la prochaine "etape" : le sommet non visité avec la distance min dans "tableau"
        double dist_min = 999999;
        int prochain_sommet = -1;
        for (int i = 0; i < n; i++) {
            if (visites[i]!=1 && tableau[i] < dist_min) {
                dist_min = tableau[i];
                prochain_sommet = i;
            }
        }
        etape = prochain_sommet;
    }

    if (etape == arrivee) {
        parcours.push_back(arrivee);}
    }

    



        
        
    }
// retourne un vecteur avec les sommets parcourus