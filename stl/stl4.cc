#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    std::vector<int>::reverse_iterator iter = find_if(v.rbegin(), v.rend(),
                                                   [] (int x) { return x % 2 == 0; });
    return iter;
}

