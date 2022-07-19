
// https://godbolt.org/z/sK55n89TM

#include <algorithm>
#include <string>

#include <fmt/core.h>
#include <fmt/ranges.h>

using namespace std::string_literals;

void rotate(auto f, auto m, auto l) {
    std::reverse(f, m);
    std::reverse(m, l);
    std::reverse(f, l);
}

int main() {

    auto conf = "C++North!"s;
    rotate(conf.begin(), conf.begin() + 3, conf.end());
    fmt::print("{}\n", conf); // North!Cpp

    return 0;
}
