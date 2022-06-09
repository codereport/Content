// Godbolt: https://www.godbolt.org/z/7hcxqd

#include <vector>
#include <algorithm>
#include <numeric>

#include "fmt/core.h"

using namespace std;

auto all_equal(auto f, auto l) {
    auto [a, b] = minmax_element(f, l);
    return *a == *b;
}

auto all_equal1(auto f, auto l) {
    return transform_reduce(f, l, true,
        std::logical_and{}, 
        [f](auto e) { return e == *f; });
}

auto all_equal2(auto f, auto l) {
    return all_of(f, l, [f](auto e) { return e == *f; });
}

auto all_equal3(auto f, auto l) {
    return adjacent_find(f, l, not_equal_to{}) == l;
}

auto all_equal4(auto f, auto l) {
    sort(f, l);
    auto i = unique(f, l);
    return distance(f, i) == 1;
}

auto main() -> int {

    auto v = std::vector{1, 1, 1};
    auto a = v.begin();
    auto b = v.end();

    fmt::print("{}\n", all_equal (a, b));
    fmt::print("{}\n", all_equal1(a, b));
    fmt::print("{}\n", all_equal2(a, b));
    fmt::print("{}\n", all_equal3(a, b));
    fmt::print("{}\n", all_equal4(a, b));

    return 0;
}
