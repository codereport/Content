#include <algorithm>
#include <numeric>
#include <print>
#include <vector>

auto rmmmi(int n) -> int {
    auto vec = std::vector<int>(n - 1);
    std::iota(vec.begin(), vec.end(), 1);
    std::transform(vec.begin(), vec.end(), vec.begin(), [](auto e) { return (e % 10) * 2 + 1; });
    return std::accumulate(vec.begin(), vec.end(), 0, std::plus{});
}

auto main() -> int {
    auto const n = 100001;
    std::print("{}", rmmmi(n));
    return 0;
}
