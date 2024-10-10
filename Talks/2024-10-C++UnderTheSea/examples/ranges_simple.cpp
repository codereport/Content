#include <algorithm>
#include <print>
#include <ranges>

auto rmmmi(int n) -> int {
    return std::ranges::fold_left(  //
      std::views::iota(1, n)        //
        | std::views::transform([](auto e) { return (e % 10) * 2 + 1; }),
      0,
      std::plus{});
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
