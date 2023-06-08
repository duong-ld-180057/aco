#include <vector>
#include <string>
#include <iostream>

#include "../header/mapNode.h"
#include "../header/pheromone.h"
#include "../header/findPath.h"
#include "../header/job.h"
#include "../header/environmentAffect.h"
#include "../header/travelTime.h"
#include "../header/waitTime.h"
#include "../header/linear_distribution/ln_targetFunction.h"
#include "../header/linear_distribution/ln_collisionCheck.h"
#include "../header/constants.h"

#include "../header/ACO.h"

using namespace std;

ACO::ACO() {

}

ACO::ACO(string mapFile) {
    map = readInput(mapFile);
    initTravelTime(&map);
    initWaitTime(&map);
    initEnvironmentAffect(&map);
}

ACO::~ACO() {
    // TODO Auto-generated destructor stub
}

string convertPath(vector<MapNode> *map, vector<int> path) {
    string result = "$";

    for (int i = 0; i < path.size(); i++) {
        // if name start with :J continue
        if ((*map)[path[i]].name[0] == ':') {
            continue;
        }
        // E123_1 -> E123
        string name = (*map)[path[i]].name.substr(0, (*map)[path[i]].name.find("_"));
        result += name + "$";
    }

    return result;
}



string ACO::findBestPath(string startEdge, string endEdge) {
    initPheromone(&map);
    vector<int> globalBestPath;
    double globalBestTargetFnValue = 0;

    int start = findNodeWithName(map, startEdge);
    int end = findNodeWithName(map, endEdge);

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        cout << endl;
        cout << "Stage " << i + 1 << endl;

        vector<int> localBestPath;
        double localBestTargetFnValue = 0;

        // find local best first half path
        for (int j = 0; j < NUM_ANTS; j++) {
            try {
                cout << "Ant " << j + 1 << ": ";

                vector<int> path = findPath(&map, start, end);

                double targetFnValue = calculateDistance(&map, path);
                cout << "Target: " << targetFnValue << endl;

                if (localBestPath.size() == 0 || (targetFnValue < localBestTargetFnValue && targetFnValue > 0)) {
                    localBestPath = path;
                    localBestTargetFnValue = targetFnValue;
                }
            } catch(const char* msg) {
                cout << msg << endl;
            }
        }
        // update pheromone
        updatePheromone(&map, localBestPath, localBestTargetFnValue);

        // update global best path
        if (globalBestPath.size() == 0 || (localBestTargetFnValue < globalBestTargetFnValue && localBestTargetFnValue > 0)) {
            globalBestPath = localBestPath;
            globalBestTargetFnValue = localBestTargetFnValue;
        }
    }

    cout << endl;

    string result = convertPath(&map, globalBestPath);
    cout << "Best path: " << result << endl;
    return result;
}
