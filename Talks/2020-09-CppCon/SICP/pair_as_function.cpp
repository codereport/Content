
// https://www.godbolt.org/z/zncs8E

#include <fmt/core.h>

enum class msg : bool { FIRST, SECOND };

auto pair(auto x, auto y) {
    return [x, y](auto m) {
        if      (m == msg::FIRST)     return x;
        else /* (m == msg::SECOND) */ return y;
    }; 
}

int main() {

    auto p = pair(42, 1729);

    fmt::print("{}\n", p(msg::FIRST));  // 42
    fmt::print("{}\n", p(msg::SECOND)); // 1729

    return 0;
}
