
#include <vector>
#include <iostream>

#include <thrust/device_vector.h>
#include <thrust/tabulate.h>

using namespace std;

auto main () -> int {

    auto odds = thrust::device_vector<int>(10);

    thrust::tabulate(
        odds.begin(), odds.end(), 
        [] __device__ (auto e) { return e * 2 + 1; });

    for (auto odd : odds) 
        std::cout << odd << ' ';

}
