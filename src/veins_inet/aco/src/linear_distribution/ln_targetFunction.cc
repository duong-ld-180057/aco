#include <vector>
#include <iostream>

#include "../../header/constants.h"
#include "../../header/mapNode.h"
#include "../../header/job.h"
#include "../../header/linear_distribution/ln_targetFunction.h"

using namespace std;

double calculatePenalty(double earliness, double tardiness, double expected) {
    if (earliness <= expected && expected <= tardiness) {
        return 0;
    }
    if (earliness > expected) {
        return earliness - expected;
    }
    return expected - tardiness;
}

double ln_calculateTargetFunctionValue(vector<MapNode> map, vector<int> path, Job job) {
    double expectedFirstHalfTime = 0;
    double expectedTotalTime = 0;
    double expectedTotalWaitTime = 0;
    double expectedTotalEnvironmentAffect = 0;
    bool isInFirstHalf = 1;

    for (int i = 0; i < path.size(); i++) {
        double expectedTimeInRoute = (map[path[i]].minTravelTime + map[path[i]].maxTravelTime) / 2;
        double expectedWaitTimeInRoute = (map[path[i]].minWaitTime + map[path[i]].maxWaitTime) / 2;

        if (isInFirstHalf) {
            expectedFirstHalfTime += expectedTimeInRoute;
            expectedTotalTime += expectedTimeInRoute;
        } else {
            expectedTotalTime += expectedTimeInRoute;
        }
        expectedTotalWaitTime += expectedWaitTimeInRoute;
        expectedTotalEnvironmentAffect += map[path[i]].environmentAffect;

        if (path[i] == job.receive) {
            isInFirstHalf = false;
        }
    }

    double lateReceivePenalty = calculatePenalty(job.earliestReceiveTime, job.tardinessReceiveTime, expectedFirstHalfTime);
    double lateEndPenalty = calculatePenalty(job.earliestEndTime, job.tardinessEndTime, expectedTotalTime);
    double targetFunctionValue = TG_ALPHA*(lateReceivePenalty + lateEndPenalty + expectedTotalWaitTime) - TG_BETA*expectedTotalEnvironmentAffect;

    return targetFunctionValue;
}
