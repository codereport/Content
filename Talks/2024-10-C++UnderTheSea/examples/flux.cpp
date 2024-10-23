#include <algorithm>
#include <print>

#include <flux.hpp>

auto rmmmi(int n) -> int {
    return flux::iota(1, n)
      .map([](auto e) { return e % 10; })
      .map([](auto e) { return e * 2; })
      .map([](auto e) { return e + 1; })
      .sum();
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
