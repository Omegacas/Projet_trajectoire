#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm> // Indispensable pour std::reverse

using namespace std;

vector<int> dijkstra(vector<vector<double>> matrice_graphe, int depart, int arrivee) {
    int n = matrice_graphe.size();

    // Sécurité immédiate : indices hors matrice
    if (depart < 0 || depart >= n || arrivee < 0 || arrivee >= n) {
        cout << "Erreur : Indices depart/arrivee hors limites !" << endl;
        return {};
    }

    vector<double> tableau(n, 999999.0);
    vector<int> visite(n, 0);
    vector<int> predecesseur(n, -1);

    // Initialisation
    tableau[depart] = 0;

    int etape = depart;
    while (etape != -1 && etape != arrivee) {
        visite[etape] = 1;

        for (int i = 0; i < n; i++) {
            // On vérifie que l'arc existe et n'est pas un obstacle
            if (matrice_graphe[etape][i] > 0 && matrice_graphe[etape][i] < 999999 && visite[i] != 1) {
                double nouvelle_dist = tableau[etape] + matrice_graphe[etape][i];
                if (nouvelle_dist < tableau[i]) {
                    tableau[i] = nouvelle_dist;
                    predecesseur[i] = etape;
                }
            }
        }

        double dist_min = 999999;
        int prochain_sommet = -1;
        for (int i = 0; i < n; i++) {
            if (visite[i] != 1 && tableau[i] < dist_min) {
                dist_min = tableau[i];
                prochain_sommet = i;
            }
        }
        etape = prochain_sommet;
    }

    // --- RECONSTRUCTION SÉCURISÉE (Plus d'indices fixes) ---
    vector<int> chemin;
    
    // Si la distance est restée à l'infini, c'est que l'arrivée est inaccessible
    if (tableau[arrivee] >= 999999) {
        cout << "Aucun chemin trouve entre " << depart << " et " << arrivee << endl;
        return chemin; 
    }

    // On remonte le fil d'Ariane
    for (int v = arrivee; v != -1; v = predecesseur[v]) {
        chemin.push_back(v);
        // Sécurité anti-boucle infinie (au cas où)
        if (chemin.size() > (size_t)n) break; 
    }

    // Le chemin est de l'arrivée vers le départ, on le retourne
    reverse(chemin.begin(), chemin.end());

    return chemin;
}