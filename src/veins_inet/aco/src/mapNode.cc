#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>

#include "../header/mapNode.h"

using namespace std;

MapNode createNode(string name, int weight) {
    MapNode node;
    node.name = name;
    node.weight = weight;

    return node;
}

int findNode(vector<MapNode> map, string name) {
    for (int i = 0; i < map.size(); i++) {
        if (map[i].name == name) {
            return i;
        }
    }

    return -1;
}

std::vector<MapNode> readInput(std::string fileName) {
    vector<MapNode> map;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Unable to open file" << endl;

        return map;
    }
    getline(file, line);
    int edgesNo = stoi(line);

    getline(file, line);
    int junctionsNo = stoi(line);

    getline(file, line);

    while(line != "") {
        // start node
        cout << line << endl;
        string from = line.substr(0, line.find(" "));
        line.erase(0, line.find(" ") + 1);
        int fromIndex = findNode(map, from);

        if (fromIndex == -1) {
            fromIndex = map.size();
            map.push_back(createNode(from, 0));
        }
        string weightString = line.substr(0, line.find(" "));
        cout << weightString << " " << stod(weightString) << endl;
        double weight = stod(weightString);

        line.erase(0, line.find(" ") + 1);
        map[fromIndex].weight = weight;

        // multiple end nodes
        while (line != "" && line.find(" ") != string::npos) {
            string to = line.substr(0, line.find(" "));
            line.erase(0, line.find(" ") + 1);
            int toIndex = findNode(map, to);

            if (toIndex == -1) {
                toIndex = map.size();
                map.push_back(createNode(to, 0));
            }

            map[fromIndex].neighbors.push_back(toIndex);
        }

        // end node
        if (line != "") {
            string to = line;
            int toIndex = findNode(map, to);

            if (toIndex == -1) {
                toIndex = map.size();
                map.push_back(createNode(to, 0));
            }

            map[fromIndex].neighbors.push_back(toIndex);
        }

        getline(file, line);
    }

    file.close();

    return map;
}

int findNodeWithName(vector<MapNode> map, string name) {
    for (int i = 0; i < map.size(); i++) {
        string nodeName = map[i].name;

        if (nodeName.find("_") != string::npos) {
            // if node name has a number (e.g. "A_1")
            nodeName = nodeName.substr(0, nodeName.find("_"));
        }

        if (nodeName == name) {
            return i;
        }
    }

    return -1;
}

void printMap(vector<MapNode> map) {
    for (int i = 0; i < map.size(); i++) {
        cout << map[i].name << " " << map[i].maxTravelTime << map[i].minTravelTime << " " << map[i].pheromone << " ";

        for (int j = 0; j < map[i].neighbors.size(); j++) {
            cout << map[map[i].neighbors[j]].name << " ";
        }

        cout << endl;
    }
}
