#include <vector>
#include <algorithm>

#include "../header/helper.h"

using namespace std;

vector<int> intersection(vector<int> v1, vector<int> v2) {
    vector<int> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));

    return v3;
}
