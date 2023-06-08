#ifndef ACO_H
#define ACO_H

#include <vector>
#include <string>

#include "mapNode.h"

using namespace std;

class ACO {
public:
    ACO();
    ACO(string mapFile);
    ~ACO();
    vector<MapNode> map;
    string findBestPath(string startEdge, string endEdge);
};

#endif
