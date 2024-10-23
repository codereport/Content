#include <execution>
#include <iostream>
#include <numeric>
#include <ranges>

auto rmmmi(int n) -> int {
    auto a = std::views::iota(1, n + 1)                              //
             | std::views::transform([](auto x) { return x % 10; })  //
             | std::views::transform([](auto x) { return 2 * x; })   //
             | std::views::transform([](auto x) { return 1 + x; });
    return std::reduce(std::execution::par_unseq,  //
                       a.begin(),
                       a.begin() + n,
                       0,
                       std::plus{});
}

auto main() -> int {
    auto const n = 100000;
    std::cout << rmmmi(n);
    return 0;
}
