
// https://www.godbolt.org/z/47KTjs

#include <vector>
#include <numeric>   

#include <range/v3/view/chunk.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>

#include <fmt/core.h>

namespace rv = ranges::views;

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

auto leibniz_pi_approximation(int n) -> double {
    return (rv::iota(0, n)
          | rv::transform([](auto e){ return 1 + 2 * e;})
          | rv::chunk(2)
          | rv::transform([](auto rng) { return 1.0 / (rng[0] * rng[1]); })
          | ranges::to<std::vector<double>> // :( 
          | hs::accumulate(0.0, std::plus{})) * 8;
}

int main () {

    fmt::print("{}\n", leibniz_pi_approximation(10000));

   return 0;
}
