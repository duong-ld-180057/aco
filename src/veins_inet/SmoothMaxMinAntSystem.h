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

#ifndef VEINS_INET_SMOOTHMAXMINANTSYSTEM_H_
#define VEINS_INET_SMOOTHMAXMINANTSYSTEM_H_

#include "ArrivalDijkstra.h"

typedef std::tuple<std::string, std::string, std::string> Itinerary;
typedef std::map<std::string, Itinerary*> Itineraries;
typedef std::map<std::string, std::string> Paths;

class SmoothMaxMinAntSystem: public ArrivalDijkstra {
public:
    Itineraries allItinerary;
    Paths allPath;
    ACO aco;
    SmoothMaxMinAntSystem();
    virtual ~SmoothMaxMinAntSystem();
    void planOut(int sourPathsce, int target, std::string currLane, AGV* cur) override;
    void getItineraries(std::string itineraryFile) override;
    std::string getRoute(std::string trace, std::string currLane, int currentVertex, int nextVertex, int exitVertex) override;
};

#endif /* VEINS_INET_SMOOTHMAXMINANTSYSTEM_H_ */
