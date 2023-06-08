#include <vector>

#include "../header/mapNode.h"
#include "../header/waitTime.h"

using namespace std;

void initWaitTime(vector<MapNode> *map) {
    for (int i = 0; i < map->size(); i++) {
        (*map)[i].minWaitTime = 0;
        (*map)[i].averageWaitTime = 5;
        (*map)[i].maxWaitTime = 10;
    }
}
