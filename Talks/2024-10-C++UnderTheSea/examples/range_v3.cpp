#include <algorithm>
#include <print>

#include <range/v3/all.hpp>

auto rmmmi(int n) -> int {
    return ranges::fold_left(                                      //
      ranges::views::iota(1, n)                                    //
        | ranges::views::transform([](auto e) { return e % 10; })  //
        | ranges::views::transform([](auto e) { return e * 2; })   //
        | ranges::views::transform([](auto e) { return e + 1; }),
      0,
      std::plus{});
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
