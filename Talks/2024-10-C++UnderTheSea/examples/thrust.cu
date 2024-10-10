#include <iostream>

#include <thrust/functional.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/reduce.h>

auto rmmmi(int n) -> int {
    auto a = thrust::make_counting_iterator(1);
    auto b = thrust::make_transform_iterator(a, [] __host__ __device__(int x) { return x % 10; });
    auto c = thrust::make_transform_iterator(b, [] __host__ __device__(int x) { return x * 2; });
    auto d = thrust::make_transform_iterator(c, [] __host__ __device__(int x) { return x + 1; });
    return thrust::reduce(d, d + n, 0, thrust::plus{});
}

auto main() -> int {
    auto const n = 100001;
    std::cout << rmmmi(n);
    return 0;
}
