#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "C:\Users\antoi\OneDrive\Desktop\Projet_trajectoire\trajectoire\includer\lecture_scene.hpp"


using namespace std;




vector<Point> parsePoints(string str) {
    vector<Point> points;
    // On remplace les caractères spéciaux par des espaces pour faciliter l'extraction
    for (char &c : str) {
        if (c == '(' || c == ')' || c == ',') c = ' ';
    }
    
    stringstream ss(str);
    double x, y;
    while (ss >> x >> y) {
        points.push_back({x, y});
    }
    return points;
}

DataRoute lireFichier(string nomFichier) {
    ifstream file(nomFichier);
    string line;
    DataRoute route; // On crée l'objet ici

    getline(file, line); // Sauter l'en-tête

    if (getline(file, line)) {
        stringstream ss(line);
        string segment;
        vector<string> colonnes;

        while (getline(ss, segment, '|')) {
            colonnes.push_back(segment);
        }

        if (colonnes.size() >= 6) {
            route.depart  = parsePoints(colonnes[0])[0];
            route.arrivee = parsePoints(colonnes[1])[0];
            
            // On remplit la liste des obstacles (liste de listes de sommets)
            route.obstacles.push_back(parsePoints(colonnes[2]));
            route.obstacles.push_back(parsePoints(colonnes[3]));
            route.obstacles.push_back(parsePoints(colonnes[4]));
            
            route.chemin = parsePoints(colonnes[5]);
        }
    }
    return route; // <--- TRÈS IMPORTANT : on renvoie l'objet rempli
}

/*int main() {
    // On récupère toutes les données du fichier
    DataRoute maRoute = lireFichier("../OBSTACLE/Obstacles_1.csv");

    // Accès à la liste des obstacles
    // maRoute.obstacles est un vector<vector<Point>>
    
    cout << "J'ai recupere " << maRoute.obstacles.size() << " obstacles." << endl;

    // Exemple : Accéder au 1er sommet du 2ème obstacle
    if (!maRoute.obstacles.empty() && maRoute.obstacles[1].size() > 0) {
        Point p = maRoute.obstacles[1][0];
        cout << "Sommet 0 de l'obstacle 1 : x=" << p.x << ", y=" << p.y << endl;
    }

    return 0;
}*/
