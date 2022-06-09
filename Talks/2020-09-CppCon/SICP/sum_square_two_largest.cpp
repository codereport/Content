
// https://www.godbolt.org/z/c47YYn

// https://quick-bench.com/q/d39Zi6wOtaC9GUm2YyfXgCxFKmM (5 elements)
// https://quick-bench.com/q/MVjDIcL_jjBxQ1oury2-6KBCFdE (1000 elements)

#include <vector>
#include <algorithm> // nth_element, transform
#include <numeric>   // accumulate

#include <fmt/core.h>

// before I removed swap
auto solution_swap(auto const& v) {
    auto const [a, b] = std::accumulate(
        std::cbegin(v),
        std::cend(v),
        std::pair{0, 0},
        [](auto acc, auto e) {
            auto [a, b] = acc;
            if      (e > a) { std::swap(a, b); a = e; } 
            else if (e > b) {                  b = e; }
            return std::pair{a, b};
        });
    return a * a + b * b;
}

// after I realized my blunder
auto solution(auto const& v) {
    auto const [a, b] = std::accumulate(
        std::cbegin(v),
        std::cend(v),
        std::pair{0, 0},
        [](auto acc, auto e) {
            auto [a, b] = acc;
            if      (e > a) { b = a; a = e; } 
            else if (e > b) { b = e; }
            return std::pair{a, b};
        });
    return a * a + b * b;
}

auto solution2(auto v) {
    using namespace std::ranges;
    nth_element(v, std::begin(v) + 2, std::greater{});
    transform(std::cbegin(v), std::cbegin(v) + 2, std::begin(v),
        [](auto e) { return e * e; });
    return std::accumulate(std::begin(v), std::begin(v) + 2, 
        0, std::plus{});
}

auto solution3(auto v) {
    using namespace std::ranges;
    nth_element(v, std::begin(v) + 2, std::greater{});
    return v[0] * v[0] + v[1] * v[1];
}

int main () {

    std::vector v = {5, 3, 1, 4, 2};

    fmt::print("{}\n", solution(v));
    fmt::print("{}\n", solution2(v));
    fmt::print("{}\n", solution3(v));

   return 0;
}
