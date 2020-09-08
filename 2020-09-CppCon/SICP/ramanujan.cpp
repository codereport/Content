// https://www.godbolt.org/z/h7aoqo

#include <iostream>
#include <ranges>

#include <range/v3/view/adjacent_filter.hpp>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/drop.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp> // to

namespace rv = ranges::views;
namespace ra = ranges::actions;

struct ram { 
    int a, b, w; 
    explicit ram(auto const& tuple) {
        auto const [x, y] = tuple;
        a = x, b = y, w = x*x*x + y*y*y;
    }
    bool operator==(ram const& o) const { 
        return w == o.w && a != o.b; 
    }
};

int main() {

    constexpr int upto = 33;

    auto wpairs = rv::cartesian_product(rv::iota(1, upto),rv::iota(1, upto)) 
        | rv::transform([](auto t) { return ram{t}; })
        | rv::filter([](auto r) { return r.a < r.b; })
        | ranges::to<std::vector<ram>>
        | ra::sort(std::less{}, &ram::w);
    
    auto ramanujans = wpairs
        | rv::adjacent_filter(std::equal_to{})
        | rv::drop(1);

    for (auto const& r : ramanujans)
        std::cout << r.w << '\n';

    return 0;
}

// ideally:

// auto ramanujans 
//     = rv::ordered_triangle_product(weight, rv::iota(1),rv::iota(1)) 
//     | rv::transform([](auto t) { return ram{t}; })
//     | rv::adjacent_filter(std::equal_to{})
//     | rv::drop(1)
//     | rv::take(5);
