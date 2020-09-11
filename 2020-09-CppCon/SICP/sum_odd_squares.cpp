
#include <iostream>
#include <numeric>
#include <vector>
#include <ranges>

#include <range/v3/view/filter.hpp> // need this for ranges::make_pipeable

namespace rv = std::ranges::views;

namespace hs {
    template <typename T, typename BinOp>
    auto accumulate(T const& init, BinOp binop) {
        return ranges::make_pipeable([&](auto&& rng) {
            return std::accumulate(
                ranges::begin(rng), 
                ranges::end(rng), 
                init, 
                binop);
        });
    }
}

auto sum_odd_squares(auto tree) {
    return tree
        | rv::join
        | rv::filter([](auto e) { return e % 2; })
        | rv::transform([](auto e) { return e * e; })
        | hs::accumulate(0, std::plus{});
}

int main() {

    auto const tree = std::vector<std::vector<int>>
        {{1, 2, 3}, {4, 5, 6}, {10, 11}};

    std::cout << sum_odd_squares(tree);

    return 0;
}
