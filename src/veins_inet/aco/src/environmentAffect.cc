#include <vector>

#include "../header/mapNode.h"

using namespace std;

void initEnvironmentAffect(vector<MapNode> *map) {
    for (int i = 0; i < map->size(); i++) {
        // random number between 0 and 1
        (*map)[i].environmentAffect = (double) rand() / RAND_MAX;
    }
}
