#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/host_vector.h>
#include <thrust/reduce.h>
#include <thrust/sequence.h>
#include <thrust/transform_reduce.h>
#include <iostream>

// Functor to square a number
struct square {
    __host__ __device__ int operator()(const int& x) const { return x * x; }
};

auto sos(int N) {
    // Create a device vector and fill it with sequence 0, 1, 2, ..., N-1
    thrust::device_vector<int> d_vec(N);
    thrust::sequence(d_vec.begin(), d_vec.end());

    // Square each element and sum the result
    return thrust::transform_reduce(
      d_vec.begin(), d_vec.end(), square(), 0, thrust::plus<int>());
}

int main() {
    auto result = sos(10);
    std::cout << result << std::endl;
    return 0;
}
