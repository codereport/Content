// https://godbolt.org/z/j9M8Kss6c

#include <algorithm>
#include <print>
#include <ranges>

auto sos(int N) {
    return std::ranges::fold_left(
      std::ranges::views::iota(0, N) |
        std::ranges::views::transform([](int x) { return x * x; }),
      0,
      std::plus{});
}

int main() { std::print("{}", sos(10)); }
