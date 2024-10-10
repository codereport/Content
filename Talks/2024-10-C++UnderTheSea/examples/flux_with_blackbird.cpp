#include <algorithm>
#include <print>

#include <combinators.hpp>
#include <flux.hpp>

using namespace combinators;

auto rmmmi(int n) -> int {
    return flux::iota(1, n)  //
      .map(mod_(10))
      .map(_mul(2))
      .map(_plus(1))
      .sum();
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
