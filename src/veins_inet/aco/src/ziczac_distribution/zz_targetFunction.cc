#include <vector>
#include <iostream>

#include "../../header/constants.h"
#include "../../header/mapNode.h"
#include "../../header/job.h"
#include "../../header/ziczac_distribution/zz_targetFunction.h"

using namespace std;

double zz_calculatePenalty(double earliness, double tardiness, double expected) {
    if (earliness <= expected && expected <= tardiness) {
        return 0;
    }
    if (earliness > expected) {
        return earliness - expected;
    }
    return expected - tardiness;
}

double zz_calculateTargetFunctionValue(vector<MapNode> map, vector<int> path, Job job) {
    double expectedFirstHalfTime = 0;
    double expectedTotalTime = 0;
    double expectedTotalWaitTime = 0;
    double expectedTotalEnvironmentAffect = 0;
    bool isInFirstHalf = 1;

    for (int i = 0; i < path.size(); i++) {
        double expectedTimeInRoute = (map[path[i]].minTravelTime + 2 * map[path[i]].averageTravelTime + map[path[i]].maxTravelTime) / 4;
        double expectedWaitTimeInRoute = (map[path[i]].minWaitTime + 2 * map[path[i]].averageWaitTime + map[path[i]].maxWaitTime) / 4;

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

    double lateReceivePenalty = zz_calculatePenalty(job.earliestReceiveTime, job.tardinessReceiveTime, expectedFirstHalfTime);
    double lateEndPenalty = zz_calculatePenalty(job.earliestEndTime, job.tardinessEndTime, expectedTotalTime);
    double targetFunctionValue = TG_ALPHA*(lateReceivePenalty + lateEndPenalty + expectedTotalWaitTime) - TG_BETA*expectedTotalEnvironmentAffect;

    return targetFunctionValue;
}
