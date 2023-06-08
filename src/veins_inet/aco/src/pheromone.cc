#include <vector>
#include <iostream>

#include "../header/mapNode.h"
#include "../header/constants.h"

using namespace std;

void initPheromone(vector<MapNode> *map) {
    for (int i = 0; i < map->size(); i++) {
        (*map)[i].pheromone = MAX_PHEROMONE;
    }
}

void updatePheromone(vector<MapNode> *map, vector<int> path, double distance) {
    for (int i = 0; i < map->size(); i++) {
        bool isInPath = false;
        double deltaPheromone = 0;

        for (int j = 0; j < path.size(); j++) {
            if (i == path[j]) {
                isInPath = true;
                break;
            }
        }

        if (!isInPath) {
            deltaPheromone = MIN_PHEROMONE * RHO;
        } else {
            deltaPheromone = MAX_PHEROMONE * RHO;
        }

        double evaporation = (1 - RHO) * (*map)[i].pheromone;
        double newPheromone = evaporation + deltaPheromone;

        (*map)[i].pheromone = newPheromone;
    }
}

void printPheromone(vector<MapNode> map) {
    for (int i = 0; i < map.size(); i++) {
        cout << map[i].name << " " << map[i].pheromone << endl;
    }
}
