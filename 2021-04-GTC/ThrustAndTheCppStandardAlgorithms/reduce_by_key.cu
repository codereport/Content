
#include <vector>
#include <iostream>

#include <thrust/iterator/discard_iterator.h>
#include <thrust/reduce.h>

using namespace std;

auto main () -> int {

    auto const ones = vector<int>{1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1};
    auto       sums = vector<int>(5);

    thrust::reduce_by_key(
        ones.cbegin(),                   // keys input
        ones.cend(),   
        ones.cbegin(),                   // values input
        thrust::make_discard_iterator(), // keys output
        sums.begin());

    auto const max = *thrust::max_element(
        sums.cbegin(), sums.cend());

    std::cout << max << '\n';

}
