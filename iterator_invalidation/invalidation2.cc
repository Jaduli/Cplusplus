#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto beg = vec.begin();
    auto end = vec.end()-2;
    if (vec.size() % 2 == 1) {
        end -= 1;
    }
    for (auto i = end; i >= beg; i = i-2)
    { vec.erase(i+1); }
}

