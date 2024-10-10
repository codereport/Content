#include <print>
#include <ranges>

auto rmmmi(int n) -> int {
    auto res = 0;
    for (int i = 1; i < n; i += 1)
        res += (i % 10) * 2 + 1;
    return res;
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
