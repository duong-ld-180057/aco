#include <vector>

#include "../../header/mapNode.h"
#include "../../header/constants.h"
#include "../../header/helper.h"
#include "../../header/ziczac_distribution/zz_collisionCheck.h"

using namespace std;

double zz_calculateExpectedTravelTime(vector<MapNode> map, vector<int> path, int targetNode) {
    double expectedTravelTime = 0;

    for (int i = 0; i < path.size(); i++) {
        if (path[i] == targetNode) {
            break;
        }
        double expectedTravelTimeInRoute = INV_ALPHA >= 0.5 ? (
            (2 - 2 * INV_ALPHA) * map[path[i]].averageTravelTime + (2 * INV_ALPHA - 1) * map[path[i]].maxTravelTime
        ): (
            (1 - 2 * INV_ALPHA) * map[path[i]].minTravelTime + 2 * INV_ALPHA * map[path[i]].averageTravelTime
        );
        expectedTravelTime += expectedTravelTimeInRoute;
    }

    return expectedTravelTime;
}

bool zz_checkCollisionBetweenTwoPaths(vector<MapNode> map, vector<int> path1, vector<int> path2) {
    vector<int> intersectionNodes = intersection(path1, path2);

    for (int i = 0; i < intersectionNodes.size(); i++) {
        double expectedTravelTime1 = zz_calculateExpectedTravelTime(map, path1, intersectionNodes[i]);
        double expectedTravelTime2 = zz_calculateExpectedTravelTime(map, path2, intersectionNodes[i]);

        if (expectedTravelTime1 == expectedTravelTime2) {
            return true;
        }
    }

    return false;
}

bool zz_checkCollision(vector<MapNode> map, vector<int> path, vector<vector<int> > paths) {
    for (int i = 0; i < paths.size(); i++) {
        if (zz_checkCollisionBetweenTwoPaths(map, path, paths[i])) {
            return true;
        }
    }

    return false;
}
