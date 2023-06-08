#ifndef LN_COLLISIONCHECK_H
#define LN_COLLISIONCHECK_H

#include <vector>

#include "../mapNode.h"

bool ln_checkCollision(std::vector<MapNode> map, std::vector<int> path, std::vector<std::vector<int> > paths);

#endif
