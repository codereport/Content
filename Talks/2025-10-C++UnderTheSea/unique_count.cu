#include <thrust/device_vector.h>
#include <thrust/inner_product.h>
#include <iostream>

#include "parrot.hpp"

template <typename I>
auto unique_count_ip(I first, I last) {
    return 1 + thrust::inner_product(first,
                                     last - 1,
                                     first + 1,
                                     0,
                                     thrust::plus{},
                                     thrust::not_equal_to{});
}

template <typename I>
auto unique_count_zip(I first, I last) {
    auto zip = thrust::make_zip_iterator(first, first + 1);
    auto map = thrust::make_transform_iterator(
      zip, thrust::make_zip_function(thrust::not_equal_to{}));
    return 1 + thrust::reduce(map, map + (last - first - 1), 0, thrust::plus{});
}

template <typename I>
auto unique_count_zip_count_if(I first, I last) {
    auto zip = thrust::make_zip_iterator(first, first + 1);
    auto neq = thrust::make_zip_function(thrust::not_equal_to{});
    return 1 + thrust::count_if(zip, zip + (last - first - 1), neq);
}

auto unique_parrot(auto data) { return data.map_adj(parrot::neq{}).sum() + 1; }
auto unique_parrot2(auto data) { return data.differ().sum() + 1; }

int main() {
    auto thrust_data = thrust::device_vector<int>{1, 1, 2, 2, 3, 3, 1, 1};
    auto f           = thrust_data.begin();
    auto l           = thrust_data.end();
    auto parrot_data = parrot::array({1, 1, 2, 2, 3, 3, 1, 1});

    std::cout << unique_count_ip(f, l) << std::endl;
    std::cout << unique_count_zip(f, l) << std::endl;
    std::cout << unique_count_zip_count_if(f, l) << std::endl;
    unique_parrot(parrot_data).print();
    unique_parrot2(parrot_data).print();
}
