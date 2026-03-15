#include <cmath>
#include <iostream>
#include <vector>
#include "../includer/lecture_scene.hpp"
#include "../includer/trajectoire.hpp"
#include "../includer/dijkstra.hpp"

using namespace std;

// Fonction pour transformer un Point (csv) en vector<double> (utilisé par la classe obstacle)
vector<double> pointToVec(Point p) {
    return {p.x, p.y};
}

graph<double> generer_graphe_complet(const DataRoute& route) {
    graph<double> global_graph;
    vector<Point> tous_les_points;

    // 1. On rassemble tous les points d'intérêt dans l'ordre

    tous_les_points.push_back(route.depart); // Index 0
    for (const auto& obs : route.obstacles) {
        for (const auto& p : obs){ 
            tous_les_points.push_back(p);
    }
}
    tous_les_points.push_back(route.arrivee); // Dernier index
    global_graph.nb_sommets = tous_les_points.size();
    int total_points = tous_les_points.size();

    // 2. On prépare les objets "obstacle" du groupe pour utiliser leur méthode intersection
    vector<obstacle<double>> liste_objets_obstacles;
    for (const auto& obs_coords : route.obstacles) {
        vector<vector<double>> sommets_doubles;
        for (const auto& p : obs_coords) sommets_doubles.push_back(pointToVec(p));
        liste_objets_obstacles.push_back(obstacle<double>(sommets_doubles));
    }

    // 3. Double boucle pour relier tous les sommets entre eux
    for (int i = 0; i < total_points; ++i) {
        for (int j = i + 1; j < total_points; ++j) {
            Point p1 = tous_les_points[i];
            Point p2 = tous_les_points[j];
            
            bool est_accessible = true;
            vector<double> depart_segment = pointToVec(p1);
            vector<double> direction = pointToVec(p2) - pointToVec(p1);

            // On vérifie si ce segment traverse l'un des obstacles via la fonction du groupe
            for (auto& obs_obj : liste_objets_obstacles) {
                // Utilisation de la fonction intersection existante
                vector<double> inter = obs_obj.intersection(depart_segment, direction);
                
                // Si une intersection est trouvée (vecteur non vide)
                if (!inter.empty()) {
                    // On vérifie que l'intersection n'est pas juste l'un des sommets p1 ou p2
                    double dist_inter = sqrt(pow(inter[0]-p1.x, 2) + pow(inter[1]-p1.y, 2));
                    double dist_totale = sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
                    
                    // Si l'intersection est strictement entre les deux points
                    if (dist_inter > 1e-4 && dist_inter < (dist_totale - 1e-4)) {
                        est_accessible = false;
                        break;
                    }
                }
            }

            // 4. Création de l'arc (on garde la structure 'arc' de trajectoire.hpp)
            arc<double> a;
            a.num1 = i;
            a.num2 = j;
            a.sommet1 = pointToVec(p1);
            a.sommet2 = pointToVec(p2);
            
            if (est_accessible) {
                a.poids = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
            }

            global_graph.arcs.push_back(a);
        }
    }

    return global_graph;
}

int main() {
    DataRoute maRoute = lireFichier("../OBSTACLE/Obstacles_1.csv");
    
    // 1. On récupère les points pour pouvoir faire la correspondance plus tard
    vector<Point> tous_les_points;
    tous_les_points.push_back(maRoute.depart);
    for (const auto& obs : maRoute.obstacles) {
        for (const auto& p : obs) tous_les_points.push_back(p);
    }
    tous_les_points.push_back(maRoute.arrivee);

    // 2. Génération et calcul (comme avant)
    graph<double> tempGraph = generer_graphe_complet(maRoute);
    int n = tempGraph.nb_sommets;
    graph<double> monGraphe(tempGraph.arcs, n);
    
    vector<int> resultat = dijkstra(monGraphe.matrice_adj, 0, n - 1);

    // 3. AFFICHAGE DES COORDONNÉES
    if (resultat.empty()) {
        cout << "Aucun chemin trouvé." << endl;
    } else {
        cout << "--- TRAJECTOIRE CALCULEE ---" << endl;
        for (int i = 0; i < resultat.size(); ++i) {
            int index_sommet = resultat[i];
            Point p = tous_les_points[index_sommet];
            
            cout << "Point " << i << " (Sommet " << index_sommet << ") : "
                 << "x = " << p.x << ", y = " << p.y << endl;
        }
        cout << "----------------------------" << endl;
    }

    return 0;
}