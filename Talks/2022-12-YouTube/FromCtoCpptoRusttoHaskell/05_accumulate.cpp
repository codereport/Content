// https://godbolt.org/z/bfY4qf8Pj
// 64 instructions using gcc 12.2 and -O3
// 76 instructions using gcc 12.2 and -O2

#include "stdio.h"
#include <ranges>
#include <numeric>

int calculate(int bottom, int top) {
    if (top > bottom) {
        auto even  = [](auto e) { return e % 2 == 0; };
        auto evens = std::views::iota(bottom, top + 1)
                   | std::views::filter(even);
        return std::accumulate(evens.begin(), evens.end(), 0);
    } else {
        return 0;
    }
}

int main()
{
    printf("%i\n", calculate(5, 12)); // 36
    printf("%i\n", calculate(5, 3));  // 0
    return 0;
}
