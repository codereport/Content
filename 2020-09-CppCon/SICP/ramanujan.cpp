// https://www.godbolt.org/z/sd797E

#include <iostream>
#include <ranges>

#include <range/v3/view/adjacent_filter.hpp>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp> // to

namespace rv = ranges::views;
namespace ra = ranges::actions;

auto ramanujan_numbers() {
    constexpr int upto = 33;

    auto sum_cubes = [](auto const& t) -> int { 
        auto const [a, b] = t;
        return (a * a * a) + (b * b * b); 
    };

    auto wpairs = rv::cartesian_product(rv::iota(1, upto),rv::iota(1, upto)) 
        | rv::filter([](auto r) { return std::get<0>(r) < std::get<1>(r); })
        | rv::transform(sum_cubes)
        | ranges::to<std::vector<int>>
        | ra::sort;
    
    auto ramanujan = wpairs
        | rv::adjacent_filter(std::equal_to{})
        | rv::drop(1);    

    for (auto const& r : ramanujan)
        std::cout << r << '\n';
}

int main() {
    ramanujan_numbers();
    return 0;
}

// ideally:

// auto ramanujans 
//     = rv::ordered_triangle_product(weight, rv::iota(1),rv::iota(1)) 
//     | rv::transform([](auto t) { return ram{t}; })
//     | rv::adjacent_filter(std::equal_to{})
//     | rv::drop(1)
//     | rv::take(5);
