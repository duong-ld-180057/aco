#ifndef MAPNODE_H
#define MAPNODE_H

#include <vector>
#include <string>

struct MapNode {
    std::string name;
    double weight;
    std::vector<int> neighbors;
    double pheromone;
    double maxTravelTime;
    double averageTravelTime;
    double minTravelTime;
    double maxWaitTime;
    double averageWaitTime;
    double minWaitTime;
    double environmentAffect;
};
typedef struct MapNode MapNode;

MapNode createNode(std::string name, int weight);
std::vector<MapNode> readInput(std::string fileName);
void printMap(std::vector<MapNode> map);
int findNodeWithName(std::vector<MapNode> map, std::string name);

#endif
