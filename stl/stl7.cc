#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return -1 if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    if (v.size() == 0) {
        return -1;
    }
    vector<int> sv = v;
    sort(sv.begin(), sv.end());

    int i = sv.size() / 2;
    int value;

    if (sv.size() % 2 == 0) {
        value = (sv[i] + sv[i-1]) / 2;
    }
    else {
        value = sv[i];
    }
    return value;
}
