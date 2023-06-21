//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "SmoothMaxMinAntSystem.h"

SmoothMaxMinAntSystem::SmoothMaxMinAntSystem() {
    // TODO Auto-generated constructor stub
    this->initialize();
    getItineraries("itinerary.txt");
    aco = ACO("input_aco.txt");
}

SmoothMaxMinAntSystem::~SmoothMaxMinAntSystem() {
    // TODO Auto-generated destructor stub
}

void SmoothMaxMinAntSystem::getItineraries(std::string itineraryFile) {
    std::ifstream file(itineraryFile);
    std::string line;
    std::string nameRoute;
    std::string nameSrc, nameStation, nameDest, nameJunc;
    std::string period, bestTime, amplitude;
    int source, indexOfStation, dst;
    if (this->itineraries.size() > 0) {
        this->itineraries.clear();
    }

    while (getline(file, line)) {
        if (line[0] != '#') {
            std::stringstream ss(line);
            getline(ss, nameRoute, ' ');
            getline(ss, nameSrc, ' ');
            getline(ss, nameStation, ' ');
            getline(ss, nameJunc, ' ');
            getline(ss, nameDest, ' ');
            getline(ss, period, ' ');
            getline(ss, bestTime, ' ');
            getline(ss, amplitude, ' ');
            source = findI_Vertex(nameSrc, false);
            indexOfStation = findI_Vertex(nameStation, false);
            Station *station = new Station(vertices[indexOfStation], bestTime,
                    amplitude, period);

            Itinerary *itinerary = new Itinerary(nameSrc, nameStation,
                    nameDest);

            allSs[vertices[indexOfStation]] = station;
            allItinerary[vertices[indexOfStation]] = itinerary;
            dst = findI_Vertex(nameDest, true);
            itineraries.push_back(
                    std::make_tuple(nameRoute, source, indexOfStation, dst));
        }
    }
    file.close();
}

void SmoothMaxMinAntSystem::planOut( //std::vector <Quad> adjList[],
        int source, int target, std::string currLane, AGV *cur) {
    cur->init(numVertices);
    cur->ShortestPath[source] = 0;

    // get job properties
    std::string jobStartPoint = std::get<0>(
            *allItinerary[vertices[cur->itinerary->indexStation]]);
    std::string jobDeliverPoint = std::get<1>(
            *allItinerary[vertices[cur->itinerary->indexStation]]);
    std::string jobEndPoint = std::get<2>(
            *allItinerary[vertices[cur->itinerary->indexStation]]);
    std::string startEdge, endEdge;

    if (cur->itinerary->indexStation == target) {
        startEdge = jobStartPoint;
        endEdge = jobDeliverPoint;
    } else {
        startEdge = jobDeliverPoint;
        endEdge = jobEndPoint;
    }

    std::string result;

    std::string key = cur->id + std::to_string(target);

    if (allPath.count(key) > 0) {
        result = allPath[key];
        cur->traces[target] = result;
        std::cout << "result: " << result << endl;
        return;
    }

//    if (endEdge == jobDeliverPoint && !cur->passedStation) {
//        result = aco.findBestPath(startEdge, endEdge);
//        allPath[key] = result;
//    } else if (endEdge == jobEndPoint && cur->passedStation) {
//        result = aco.findBestPath(startEdge, endEdge);
//        allPath[key] = result;
//    }

    result = aco.findBestPath(startEdge, endEdge);
    allPath[key] = result;

    cur->traces[target] = result;
    std::cout << "result: " << result << endl;
}

std::string SmoothMaxMinAntSystem::getRoute(std::string trace, std::string currLane,
        int currentVertex, int nextVertex, int exitVertex) {

    std::cout << "trace: " << trace << endl;
    if (currLane.length() > 0) {
        if (currLane[0] == '^') {
            currLane = currLane.substr(1);
        }
    }

    std::string route = (currLane[0] == ':') ? "" : (currLane + " ");
    std::string temp = "";
    std::string prevTemp = "";
    std::string strCurrVertex = this->vertices[currentVertex];
    std::string strNextVertex = this->vertices[nextVertex];
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].first.find("$" + currLane + "$") != std::string::npos) {
            std::vector<std::string> list = split(edges[i].first,
                    "$" + currLane + "$");
            std::string remaining = list[list.size() - 1];
            for (int j = 0; j < remaining.length(); j++) {
                if (remaining[j] != '$' && remaining[j] != '_') {
                    temp = temp + remaining[j];
                } else {

                    if (temp[0] != ':'
                            && route.find(temp + " ") == std::string::npos) {
                        route = route + temp + " ";
                    } else if (temp[0] != ':' && temp.compare(prevTemp) != 0
                            && (temp[0] == 'E' || temp[1] == 'E')) {
                        route = route + temp + " ";
                    }
                    prevTemp = temp;
                    temp = "";
                }
            }
            break;
        }
    }

    temp = "";
    prevTemp = "";
    int start = locateLast(route, trace);
    start = (start < 0) ? 1 : start;
    for (int i = start; i < trace.length(); i++) {
        if (trace[i] != '$' && trace[i] != '_') {
            temp = temp + trace[i];
        } else {

            if (temp[0] != ':' && route.find(temp + " ") == std::string::npos) {
                route = route + temp + " ";
            } else if (temp[0] != ':' && temp.compare(prevTemp) != 0
                    && (temp[0] == 'E' || temp[1] == 'E')) {
                route = route + temp + " ";
            }
            prevTemp = temp;
            temp = "";
        }
    }
    if (nextVertex == exitVertex)
        route = route + this->getFinalSegment(trace);

    std::cout << "Route: " << route << endl;
    return route;
}

