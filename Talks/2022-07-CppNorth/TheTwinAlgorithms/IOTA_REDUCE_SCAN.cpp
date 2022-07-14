
// https://godbolt.org/z/74cdTrcde

#include <functional>

#include <range/v3/algorithm/fold_left.hpp> 
#include <range/v3/view/iota.hpp> 
#include <range/v3/view/partial_sum.hpp> 

#include <fmt/core.h>
#include <fmt/ranges.h>

namespace rv = ranges::views;

int main() {

    auto a = rv::iota(1, 6);
    auto b = ranges::fold_left_first(rv::iota(1, 6), std::plus{}).value();
    auto c = rv::iota(1, 6) | rv::partial_sum;

    fmt::print("{}\n", a);  // [1, 2, 3, 4, 5]
    fmt::print("{}\n", b);  // 15
    fmt::print("{}\n", c);  // [1, 3, 6, 10, 15]

    return 0;
}
