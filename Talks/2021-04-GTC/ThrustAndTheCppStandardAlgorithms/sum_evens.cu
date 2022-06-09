// CUDA Thrust version

#include <numeric>
#include <vector>
#include <iostream>

#include <thrust/transform_reduce.h>

using namespace std;

auto main () -> int {

    auto const vals = vector<int>{42, 1729, 4104};

    auto const sum_evens = thrust::transform_reduce(
        vals.cbegin(), vals.cend(), 
        [](auto val) { return val % 2 == 0 ? val : 0; }, 
        0,
        thrust::plus<int>{});

    std::cout << sum_evens; // 4146

}
