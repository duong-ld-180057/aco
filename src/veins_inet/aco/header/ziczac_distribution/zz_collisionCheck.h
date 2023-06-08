#ifndef ZZ_COLLISIONCHECK_H
#define ZZ_COLLISIONCHECK_H

#include <vector>

#include "../mapNode.h"

bool zz_checkCollision(std::vector<MapNode> map, std::vector<int> path, std::vector<std::vector<int> > paths);

#endif
