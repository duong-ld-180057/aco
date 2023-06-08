#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "../header/job.h"
#include "../header/mapNode.h"

using namespace std;

vector<Job> readJobs(vector<MapNode> map, string fileName) {
    vector<Job> jobs;
    ifstream file(fileName);
    string line;

    if (!file.is_open()) {
        cout << "Unable to open file" << endl;

        return jobs;
    }
    getline(file, line);
    int jobsNo = stoi(line);

    for (int i = 0; i < jobsNo; i++) {
        getline(file, line);

        string startEdge = line.substr(0, line.find(" "));
        int start = findNodeWithName(map, startEdge);
        line.erase(0, line.find(" ") + 1);

        string receiveEdge = line.substr(0, line.find(" "));
        int receive = findNodeWithName(map, receiveEdge);
        line.erase(0, line.find(" ") + 1);

        string endEdge = line.substr(0, line.find(" "));
        int end = findNodeWithName(map, endEdge);
        line.erase(0, line.find(" ") + 1);

        double earliestReceiveTime = stod(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);

        double tardinessReceiveTime = stod(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);

        double earliestEndTime = stod(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);

        double tardinessEndTime = stod(line.substr(0, line.find(" ")));
        line.erase(0, line.find(" ") + 1);

        if (start == -1 || receive == -1 || end == -1) {
            cout << "Invalid start or end node" << endl;

            return jobs;
        }
        if (earliestReceiveTime < 0 || tardinessReceiveTime < 0 || earliestEndTime < 0 || tardinessEndTime < 0) {
            cout << "Invalid time" << endl;

            return jobs;
        }

        Job job;
        job.start = start;
        job.receive = receive;
        job.end = end;
        job.earliestReceiveTime = earliestReceiveTime;
        job.tardinessReceiveTime = tardinessReceiveTime;
        job.earliestEndTime = earliestEndTime;
        job.tardinessEndTime = tardinessEndTime;

        jobs.push_back(job);
    }

    return jobs;
}

void printJobs(vector<Job> jobs) {
    for (int i = 0; i < jobs.size(); i++) {
        cout << "Job " << i << ": " << endl;
        cout << "Start: " << jobs[i].start << endl;
        cout << "Receive: " << jobs[i].receive << endl;
        cout << "End: " << jobs[i].end << endl;
        cout << "Earliest receive time: " << jobs[i].earliestReceiveTime << endl;
        cout << "Tardiness receive time: " << jobs[i].tardinessReceiveTime << endl;
        cout << "Path: ";
        for (int j = 0; j < jobs[i].path.size(); j++) {
            cout << jobs[i].path[j] << " ";
        }
        cout << endl;
        cout << "Target function value: " << jobs[i].targetFunctionValue << endl;
        cout << endl;
    }
}

void sortJobsByStartTime(vector<Job> *jobs) {
    for (int i = 0; i < jobs->size() - 1; i++) {
        for (int j = i + 1; j < jobs->size(); j++) {
            if ((*jobs)[i].earliestReceiveTime > (*jobs)[j].earliestReceiveTime) {
                Job temp = (*jobs)[i];
                (*jobs)[i] = (*jobs)[j];
                (*jobs)[j] = temp;
            }
        }
    }
}
