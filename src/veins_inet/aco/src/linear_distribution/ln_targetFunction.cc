#include <vector>
#include <iostream>

#include "../../header/constants.h"
#include "../../header/mapNode.h"
#include "../../header/job.h"
#include "../../header/linear_distribution/ln_targetFunction.h"

using namespace std;

double calculatePenalty(double startTime, double earliness, double tardiness, double expected) {
    double expectedArrivalTime = expected + startTime;

    if (earliness <= expectedArrivalTime && expectedArrivalTime <= tardiness) {
        return 0;
    }
    if (earliness > expectedArrivalTime) {
        return earliness - expectedArrivalTime;
    }
    return expectedArrivalTime - tardiness;
}

double ln_calculateTargetFunctionValue(vector<MapNode> map, vector<int> path, double startTime, double earliestTime, double tardinessTime) {
    double expectedTotalTravelTime = 0;
    double expectedTotalWaitTime = 0;
    double expectedTotalEnvironmentAffect = 0;

    for (int i = 0; i < path.size(); i++) {
        double expectedTimeInRoute = (map[path[i]].minTravelTime + map[path[i]].maxTravelTime) / 2;
        double expectedWaitTimeInRoute = (map[path[i]].minWaitTime + map[path[i]].maxWaitTime) / 2;

        expectedTotalTravelTime += expectedTimeInRoute;
        expectedTotalWaitTime += expectedWaitTimeInRoute;
        expectedTotalEnvironmentAffect += map[path[i]].environmentAffect;
    }

    double latePenalty = 0;

    if (earliestTime > 0 && tardinessTime > 0) {
        latePenalty = calculatePenalty(startTime, earliestTime, tardinessTime, expectedTotalTravelTime);
    }

    double targetFunctionValue = TG_ALPHA*(latePenalty + expectedTotalWaitTime) - TG_BETA*expectedTotalEnvironmentAffect;

    return targetFunctionValue;
}
