#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    vector<int> j1, j2, s3;

    std::copy_if(v.begin(), v.end(), std::back_inserter(s3),
                 [](int x) { return x % 3 == 0; });
    std::copy_if(v.begin(), v.end(), std::back_inserter(j1),
                 [](int x) { return x % 3 == 1; });
    std::copy_if(v.begin(), v.end(), std::back_inserter(j2),
                 [](int x) { return x % 3 == 2; });

    sort(j1.begin(), j1.end());
    sort(j2.begin(), j2.end());
    sort(s3.begin(), s3.end());

    v.clear();
    v.insert(v.end(), s3.begin(), s3.end());
    v.insert(v.end(), j1.begin(), j1.end());
    v.insert(v.end(), j2.begin(), j2.end());

    return EXIT_SUCCESS;
}

