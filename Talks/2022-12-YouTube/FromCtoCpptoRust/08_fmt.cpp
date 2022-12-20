// https://godbolt.org/z/7nzE6KbPW
// 68 instructions using gcc 12.2 and -O3
// 80 instructions using gcc 12.2 and -O2

#include <ranges>
#include <numeric>
#include <range/v3/all.hpp>
#include <fmt/core.h>

namespace rv = std::views;

int calculate(int bottom, int top) {
    return top <= bottom ? 0 :
        ranges::accumulate(
            rv::iota(bottom, top + 1) |
            rv::filter([](auto e) { return e % 2 == 0; }), 0);
}

int main() {
    fmt::print("{}\n", calculate(5, 12));  // 36
    fmt::print("{}\n", calculate(5, 3));   // 0
    return 0;
}
