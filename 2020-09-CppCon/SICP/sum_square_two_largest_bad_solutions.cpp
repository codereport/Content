
// https://www.godbolt.org/z/Pb1qzv

// https://quick-bench.com/q/kwNxQYx5NXa6alSJGPiSM_xaECo

#include <algorithm>
#include <numeric>

#include <fmt/core.h>

int wrong_solution(std::vector<int> const& v) {
    int a = 0;
    for (int i = 0; i < v.size(); ++i)
        if (v[i] > a) a = v[i];
    
    int b = 0;
    for (int i = 0; i < v.size(); ++i)
        if (v[i] != a && v[i] > b) b = v[i];

    return a * a + b * b;
}

int bad_solution(std::vector<int> const& v) {
    int a = 0, idx = 0;
    for (int i = 0; i < v.size(); ++i)
        if (v[i] > a) a = v[i], idx = i;
    
    int b = 0;
    for (int i = 0; i < v.size(); ++i)
        if (i != idx && v[i] > b) b = v[i];

    return a * a + b * b;
}

int bad_solution_2(std::vector<int> v) {
    auto a = std::ranges::max_element(v);
    auto t = *a;
    v.erase(a);
    auto b = std::ranges::max_element(v);
    return t * t + *b * *b;
}

int bad_solution_3(std::vector<int> const& v) {
    auto a = std::ranges::max_element(v);
    auto i = distance(begin(v), a);
    auto b = std::accumulate(std::cbegin(v), std::cend(v), 0,
        [i, j = -1](auto acc, auto e) mutable {
            return --j != i ? std::max(acc, e) : acc;
        });
    return *a * *a + b * b;
}

int one_for_loop(std::vector<int> const& v) {
    int a = 0, b = 0;
    for (auto e : v)
        if      (e > a) { b = a; a = e; } 
        else if (e > b) { b = e; }
    return a * a + b * b;
}

int main () {

    fmt::print("{}\n", wrong_solution({3, 2, 3}));
    fmt::print("{}\n", bad_solution({3, 2, 3}));
    fmt::print("{}\n", bad_solution_2({3, 2, 3}));
    fmt::print("{}\n", bad_solution_3({3, 2, 3}));
    fmt::print("{}\n", one_for_loop({3, 2, 3}));

   return 0;
}
