#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform_reduce.h>
#include <iostream>

auto sos(int N) -> int {
    auto iota = thrust::counting_iterator<int>(0);
    return thrust::transform_reduce(
      iota,
      iota + N,
      [] __host__ __device__(int x) { return x * x; },
      0,
      thrust::plus<int>());
}

int main() {
    auto result = sos(10);
    std::cout << result << std::endl;
    return 0;
}
