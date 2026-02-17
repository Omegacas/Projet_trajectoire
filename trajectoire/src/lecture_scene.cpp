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
    std::vector<std::vector<Point>> obstacles;
    std::vector<Point> chemin;
};

std::vector<Point> parsePoints(std::string str) {
    std::vector<Point> points;
    // On remplace les caractères spéciaux par des espaces pour faciliter l'extraction
    for (char &c : str) {
        if (c == '(' || c == ')' || c == ',') c = ' ';
    }
    
    std::stringstream ss(str);
    double x, y;
    while (ss >> x >> y) {
        points.push_back({x, y});
    }
    return points;
}

void lireFichier(std::string nomFichier) {
    std::ifstream file(nomFichier);
    std::string line;

    // 1. Sauter l'en-tête
    std::getline(file, line);

    // 2. Lire la ligne de données
    if (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> colonnes;

        // Découpage par le caractère '|'
        while (std::getline(ss, segment, '|')) {
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
