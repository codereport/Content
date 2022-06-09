
// before

#include <vector>
#include <iostream>

#include <thrust/sequence.h>

using namespace std;

auto main () -> int {

    auto ints = vector<int>(10);
    thrust::sequence(ints.begin(), ints.end(), 0);

    for (auto i : ints) 
        std::cout << i << ' ';

}

// after

#include <vector>
#include <iostream>

#include <thrust/iterator/counting_iterator.h>

using namespace std;

auto main () -> int {

    auto       it   = thrust::make_counting_iterator(0);
    auto const ints = vector<int>(it, it + 10);

    for (auto i : ints) 
        std::cout << i << ' ';

}
