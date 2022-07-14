
// https://godbolt.org/z/jEYvh9hYv

#include <functional>
#include <string_view>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/chunk.hpp> 
#include <range/v3/view/cartesian_product.hpp> 
#include <range/v3/view/transform.hpp> 
#include <range/v3/algorithm/fold_left.hpp> 

#include <fmt/core.h>
#include <fmt/ranges.h>

using namespace std::string_view_literals;

namespace rv = ranges::views;

auto outer_product(auto left, auto right, auto binop) {
    return rv::cartesian_product(left, right)
         | rv::transform([=](auto t) { return std::apply(binop, t); })
         | rv::chunk(ranges::distance(right));
}

auto count_lrud(std::string_view sv) {
    return outer_product("LRUD"sv, sv, std::equal_to{})
        | rv::transform([](auto r) { 
            return ranges::fold_left_first(r, std::plus{}).value(); });
}

int main() {
    fmt::print("{}\n", count_lrud("LRDLURDLURDULR"));

    return 0;
}