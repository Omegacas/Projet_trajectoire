#ifndef LECTURE_SCENE_HPP
#define LECTURE_SCENE_HPP

#include <string>
#include <vector>

struct Point {
    double x;
    double y;
};

struct DataRoute {
    Point depart;
    Point arrivee;
    std::vector<std::vector<Point>> obstacles;
    std::vector<Point> chemin;
};
DataRoute lireFichier(std::string nomFichier);

#endif