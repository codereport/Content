
// https://godbolt.org/z/jxa4jcPYh

#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

int main() {

    // iota 5
    auto a = std::vector<int>(5);
    std::iota(a.begin(), a.end(), 1);
    // + reduce iota 5
    auto t = std::vector<int>(5);
    std::iota(t.begin(), t.end(), 1);
    auto b = std::accumulate(t.cbegin(), t.cend(), 0);
    // + scan iota 5
    auto c = std::vector<int>(5);
    std::iota(c.begin(), c.end(), 1);
    std::partial_sum(c.cbegin(), c.cend(), c.begin());

    for (auto e : a) std::cout << e << ' ';
    std::cout << '\n';
    std::cout << b << '\n';
    for (auto e : c) std::cout << e << ' ';
    std::cout << '\n';

    return 0;
}