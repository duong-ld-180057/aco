#include <vector>

#include "../../header/mapNode.h"
#include "../../header/constants.h"
#include "../../header/helper.h"
#include "../../header/linear_distribution/ln_collisionCheck.h"

using namespace std;

double calculateExpectedTravelTime(vector<MapNode> map, vector<int> path, int targetNode) {
    double expectedTravelTime = 0;

    for (int i = 0; i < path.size(); i++) {
        if (path[i] == targetNode) {
            break;
        }
        expectedTravelTime += INV_ALPHA * map[path[i]].minTravelTime + (1 - INV_ALPHA) * map[path[i]].maxTravelTime;
    }

    return expectedTravelTime;
}

bool checkCollisionBetweenTwoPaths(vector<MapNode> map, vector<int> path1, vector<int> path2) {
    vector<int> intersectionNodes = intersection(path1, path2);

    for (int i = 0; i < intersectionNodes.size(); i++) {
        double expectedTravelTime1 = calculateExpectedTravelTime(map, path1, intersectionNodes[i]);
        double expectedTravelTime2 = calculateExpectedTravelTime(map, path2, intersectionNodes[i]);

        if (expectedTravelTime1 == expectedTravelTime2) {
            return true;
        }
    }

    return false;
}

bool ln_checkCollision(vector<MapNode> map, vector<int> path, vector<vector<int> > paths) {
    for (int i = 0; i < paths.size(); i++) {
        if (checkCollisionBetweenTwoPaths(map, path, paths[i])) {
            return true;
        }
    }

    return false;
}
