#include <iterator>
#include <map>
#include <algorithm>

using namespace std;


/**
 * @brief From a map find the first element, whose value is at least given limit
 *        regardless of the key of the element. Return only the value or
 *        -1 if none of the values match the the search criteria.
 * @param m map that is scanned trough
 * @param given limit for the values to search
 * @return int the real found value
 */
int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
    auto it = find_if(m.begin(), m.end(),
                      [given] (const std::pair<const std::string, int>& p)
                      { return p.second >= given; });

    if (it != m.end()) {
        return it->second;
    }
    return -1;
}
