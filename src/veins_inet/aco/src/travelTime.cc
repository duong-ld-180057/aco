#include <vector>
#include <string>

#include "../header/constants.h"
#include "../header/mapNode.h"
#include "../header/travelTime.h"

using namespace std;

void initTravelTime(vector<MapNode> *map) {
    for (int i = 0; i < map->size(); i++) {
        (*map)[i].minTravelTime = (*map)[i].weight / AVERAGE_SPEED;
        (*map)[i].averageTravelTime = (*map)[i].weight / AVERAGE_SPEED + 1;
        (*map)[i].maxTravelTime = (*map)[i].weight / AVERAGE_SPEED + 2;
    }
}
