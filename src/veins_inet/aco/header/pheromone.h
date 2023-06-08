#ifndef PHEROMONE_H
#define PHEROMONE_H

#include <vector>

#include "mapNode.h"

void initPheromone(std::vector<MapNode> *map);
void updatePheromone(std::vector<MapNode> *map, std::vector<int> path, double distance);
void printPheromone(std::vector<MapNode> map);

#endif
