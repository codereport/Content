#include <algorithm>
#include <numeric>
#include <print>
#include <ranges>

auto rmmmi(int n) -> int {
    auto i = std::views::iota(1);
    return std::transform_reduce(  //
      i.begin(),
      i.begin() + n,
      0,
      std::plus{},
      [](auto e) { return (e % 10) * 2 + 1; });
}

auto main() -> int {
    auto const n = 100000;
    std::print("{}", rmmmi(n));
    return 0;
}
