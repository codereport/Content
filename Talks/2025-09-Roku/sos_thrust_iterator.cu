#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/reduce.h>
#include <iostream>

auto sos(int N) -> int {
    auto iota = thrust::counting_iterator<int>(0);
    auto map  = thrust::make_transform_iterator(
      iota, [] __host__ __device__(int x) { return x * x; });
    return thrust::reduce(map, map + N, 0);
}

int main() {
    auto result = sos(10);
    std::cout << result << std::endl;
    return 0;
}
