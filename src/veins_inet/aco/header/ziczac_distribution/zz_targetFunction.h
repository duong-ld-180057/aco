#ifndef ZZ_TARGETFUNCTION_H
#define ZZ_TARGETFUNCTION_H

#include <vector>

#include "../mapNode.h"
#include "../job.h"

double zz_calculateTargetFunctionValue(std::vector<MapNode> map, std::vector<int> path, Job job);

#endif
