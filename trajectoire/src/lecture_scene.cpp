#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct Point {
    double x, y;
};

struct DataRoute {
    Point depart;
    Point arrivee;
    vector<vector<Point>> obstacles;
    vector<Point> chemin;
};

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

void lireFichier(string nomFichier) {
    ifstream file(nomFichier);
    string line;

    // 1. Sauter l'en-tête
    getline(file, line);

    // 2. Lire la ligne de données
    if (getline(file, line)) {
        stringstream ss(line);
        string segment;
        vector<string> colonnes;

        // Découpage par le caractère '|'
        while (getline(ss, segment, '|')) {
            colonnes.push_back(segment);
        }

        if (colonnes.size() < 6) return;

        DataRoute route;
        route.depart    = parsePoints(colonnes[0])[0];
        route.arrivee   = parsePoints(colonnes[1])[0];
        route.obstacles.push_back(parsePoints(colonnes[2]));
        route.obstacles.push_back(parsePoints(colonnes[3]));
        route.obstacles.push_back(parsePoints(colonnes[4]));
        route.chemin    = parsePoints(colonnes[5]);

        // Exemple d'affichage pour vérifier
        cout << "Depart: (" << route.depart.x << "," << route.depart.y << ")" << endl;
                
                // Supposons que vous avez déjà appelé : DataRoute route = lireFichier("...");

        cout << "--- Affichage des Obstacles de la Route ---" << endl;

        int numObs = 1;
        for (const auto& obstacle : route.obstacles) {
            cout << "Obstacle " << numObs++ << " contient " << obstacle.size() << " points : ";
            
            for (const auto& p : obstacle) {
                cout << "(" << p.x << ", " << p.y << ") ";
            }
            
            cout << endl; // Saut de ligne entre chaque obstacle
        }
        cout << "Nombre de points dans le chemin: " << route.chemin.size() << endl;
    }
}
int main() {
    lireFichier("../OBSTACLE/Obstacles_1.csv");
    return 0;
}
