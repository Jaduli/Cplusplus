#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    vec.reserve(2*vec.size());

    Iter begin = vec.begin();
    Iter end = vec.end()-1;
    for ( Iter it = end; it >= begin; it--){
        if ( *it % 2 == 0 ){
            vec.insert(it+1, *it);;
        }
        else {
            vec.erase(it);;
        }
    }
    vec.shrink_to_fit();
}

