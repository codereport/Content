
// https://www.godbolt.org/z/Eh181a

#include <iostream>

enum class msg : bool { FIRST, SECOND };

auto pair(auto x, auto y) {
    return [x, y](auto m) {
        if      (m == msg::FIRST)     return x;
        else /* (m == msg::SECOND) */ return y;
    }; 
}

int main() {

    auto p = pair(42, 1729);

    std::cout << p(msg::FIRST)  << '\n'; // 42
    std::cout << p(msg::SECOND) << '\n'; // 1729

    return 0;
}
