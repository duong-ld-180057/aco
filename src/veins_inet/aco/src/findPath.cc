#include <vector>
#include <iostream>

#include "../header/mapNode.h"
#include "../header/pheromone.h"
#include "../header/constants.h"
#include "../header/linear_distribution/ln_targetFunction.h"
#include "../header/linear_distribution/ln_collisionCheck.h"
#include "../header/findPath.h"

using namespace std;

double calculateDistance(vector<MapNode> *map, vector<int> path) {
    double distance = 0;

    for (int i = 0; i < path.size(); i++) {
        int node1 = path[i];
        distance += (*map)[node1].weight;
    }
    return distance;
}

int chooseNextNode(vector<int> possibleNodes, vector<double> possiblePheromone) {
    double totalPheromone = 0;

    for (int i = 0; i < possiblePheromone.size(); i++) {
        totalPheromone += possiblePheromone[i];
    }

    double random = (double) rand() / RAND_MAX;
    double cumulativeProbability = 0;
    for (int i = 0; i < possiblePheromone.size(); i++) {
        cumulativeProbability += possiblePheromone[i] / totalPheromone;
        if (random <= cumulativeProbability) {
            return possibleNodes[i];
        }
    }

    return possibleNodes[possibleNodes.size() - 1];
}

vector<int> validateNodes(vector<MapNode> map, vector<int> possibleNodes, vector<int> visitedNodes) {
    vector<int> validNodes;

    for (int i = 0; i < possibleNodes.size(); i++) {
        bool isValid = true;

        for (int j = 0; j < visitedNodes.size(); j++) {
            if (possibleNodes[i] == visitedNodes[j]) {
                isValid = false;
            }
        }
        if (map[possibleNodes[i]].name == "OUT") {
            isValid = false;
        }
        if (isValid) {
            validNodes.push_back(possibleNodes[i]);
        }
    }

    return validNodes;
}

vector<int> findPath(vector<MapNode> *map, int start, int end) {
    vector<int> path;
    vector<int> visitedNodes;

    path.push_back(start);
    visitedNodes.push_back(start);

    int currentNode = start;

    while (currentNode != end) {
        vector<int> possibleNodes = (*map)[currentNode].neighbors;
        possibleNodes = validateNodes(*map, possibleNodes, visitedNodes);

        if (possibleNodes.size() == 0) {
            currentNode = path[path.size() - 2];
            path.pop_back();

            if (path.size() == 0) {
                throw "No path found";
            }
            continue;
        }
        vector<double> possiblePheromone;

        for (int i = 0; i < possibleNodes.size(); i++) {
            possiblePheromone.push_back((*map)[possibleNodes[i]].pheromone);
        }
        int nextNode = chooseNextNode(possibleNodes, possiblePheromone);
        currentNode = nextNode;

        path.push_back(nextNode);
        visitedNodes.push_back(nextNode);
    }

    return path;
}

vector<int> findBestPath(vector<MapNode> *map, vector<Job> jobs, int jobIndex, vector<vector<int> > currentPaths) {
    vector<int> globalBestPath;
    double globalBestTargetFnValue = 0;
//
//    int start = jobs[jobIndex].start;
//    int receive = jobs[jobIndex].receive;
//    int end = jobs[jobIndex].end;
//
//    for (int i = 0; i < NUM_ITERATIONS; i++) {
//        cout << endl;
//        cout << "Stage " << i + 1 << endl;
//
//        vector<int> localBestPath;
//        double localBestTargetFnValue = 0;
//
//        // find local best first half path
//        for (int j = 0; j < NUM_ANTS; j++) {
//            try {
//                cout << "Ant " << j + 1 << ": ";
//
//                vector<int> firstHalfPath = findPath(map, start, receive);
//                vector<int> secondHalfPath = findPath(map, receive, end);
//
//                vector<int> path;
//                path.insert(path.end(), firstHalfPath.begin(), firstHalfPath.end() - 1  );
//                path.insert(path.end(), secondHalfPath.begin(), secondHalfPath.end());
//
//                bool isCollision = ln_checkCollision(*map, path, currentPaths);
//
//                if (isCollision) {
//                    cout << "Collision" << endl;
//                    continue;
//                }
//
//                double targetFnValue = ln_calculateTargetFunctionValue(*map, path, jobs[jobIndex]);
//                cout << targetFnValue << endl;
//
//                if (localBestPath.size() == 0 || (targetFnValue < localBestTargetFnValue && targetFnValue > 0)) {
//                    localBestPath = path;
//                    localBestTargetFnValue = targetFnValue;
//                }
//            } catch(const char* msg) {
//                throw msg;
//            }
//        }
//        // update pheromone
//        updatePheromone(map, localBestPath, localBestTargetFnValue);
//
//        // update global best path
//        if (globalBestPath.size() == 0 || (localBestTargetFnValue < globalBestTargetFnValue && localBestTargetFnValue > 0)) {
//            globalBestPath = localBestPath;
//            globalBestTargetFnValue = localBestTargetFnValue;
//        }
//    }

    return globalBestPath;
}
