
// https://www.godbolt.org/z/3c4G5e

#include <fmt/core.h>

template <typename T>
auto add(T a, T b) -> T { return a + b; }
// auto add(auto a, auto b) -> decltype(auto) { return a + b; }
// auto add(auto a, auto b) { return a + b; }

auto main() -> int {
    fmt::print("{}\n", add(1, 2));
    return 0;
}
