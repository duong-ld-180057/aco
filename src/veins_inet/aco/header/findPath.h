#ifndef FINDPATH_H
#define FINDPATH_H

#include <vector>
#include "mapNode.h"
#include "pheromone.h"
#include "job.h"


double calculateDistance(std::vector<MapNode> *map, std::vector<int> path);
std::vector<int> findPath(std::vector<MapNode> *map, int start, int end);
std::vector<int> findBestPath(std::vector<MapNode> *map, std::vector<Job> jobs, int jobIndex, std::vector<std::vector<int> > currentPaths);

#endif
