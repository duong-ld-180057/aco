#ifndef JOB_H
#define JOB_H

#include <vector>
#include <string>

#include "mapNode.h"

struct Job {
    int start;
    int receive;
    int end;
    double startTime;
    double earliestReceiveTime;
    double tardinessReceiveTime;
    double earliestEndTime;
    double tardinessEndTime;
    std::vector<int> path;
    double targetFunctionValue;
};
typedef struct Job Job;

std::vector<Job> readJobs(std::vector<MapNode> map, std::string fileName);
void printJobs(std::vector<Job> jobs);
void sortJobsByStartTime(std::vector<Job> *jobs);

#endif

