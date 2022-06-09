
// https://www.godbolt.org/z/61vn9v

#include <fmt/core.h>

// auto add(int a, int b) -> int { return a + b; }

template <typename T>
auto add(T a, T b) -> T { return a + b; }
// auto add(auto a, auto b) -> decltype(auto) { return a + b; }
// auto add(auto a, auto b) { return a + b; }

auto main() -> int {
    fmt::print("{}\n", add(1, 2));
    return 0;
}
