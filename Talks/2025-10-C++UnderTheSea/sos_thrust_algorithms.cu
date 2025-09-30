#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/transform_reduce.h>
#include <iostream>

auto sos(int N) -> int {
    thrust::device_vector<int> d_vec(N);
    thrust::sequence(d_vec.begin(), d_vec.end());
    return thrust::transform_reduce(
      d_vec.begin(),
      d_vec.end(),
      [] __host__ __device__(int x) { return x * x; },
      0,
      thrust::plus<int>());
}

int main() {
    auto result = sos(10);
    std::cout << result << std::endl;
    return 0;
}
