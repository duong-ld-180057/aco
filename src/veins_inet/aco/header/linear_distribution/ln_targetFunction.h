#ifndef LN_TARGETFUNCTION_H
#define LN_TARGETFUNCTION_H

#include <vector>

#include "../mapNode.h"
#include "../job.h"

double ln_calculateTargetFunctionValue(std::vector<MapNode> map, std::vector<int> path, double startTime, double earliestTime, double tardinessTime);

#endif
