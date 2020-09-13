
// https://www.godbolt.org/z/joh4c3

#include <vector>
#include <numeric>   

#include <range/v3/view/chunk.hpp>
#include <range/v3/view/common.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/zip_with.hpp>

#include <fmt/core.h>

namespace rv = ranges::views;

namespace hs {
    template <typename T, typename BinOp>
    auto accumulate(T const& init, BinOp binop) {
        return ranges::make_pipeable([&](auto&& rng) {
            auto t = rng | rv::common;
            return std::accumulate(
                ranges::begin(t), 
                ranges::end(t), 
                init, 
                binop);
        });
    }
}

auto leibniz_pi_approximation(int n) {
    return (rv::iota(0, n)
          | rv::transform([](auto e){ return 1 + 2 * e;})
          | rv::chunk(2)
          | rv::transform([](auto rng) { return 1.0 / (rng[0] * rng[1]); })
          | hs::accumulate(0.0, std::plus{})) * 8;
}

auto leibniz_pi_approximation2(int n) {
    std::vector signs = {1,-1};
    return (rv::zip_with(
                [](auto e, auto sign) { return sign * 1.0 / e; }, 
                rv::iota(0, n) | rv::transform([](auto e){ return 1 + 2 * e;}),
                rv::cycle(signs))
          | hs::accumulate(0.0, std::plus{})) * 4;
}

auto leibniz_pi_approximation2_alt(int n) {
    return (rv::iota(0, n) 
          | rv::transform([s = -1](auto e) mutable { 
              s = s > 0 ? -1 : 1;
              return s * 1.0 / (1 + 2 * e); })
          | hs::accumulate(0.0, std::plus{})) * 4;
}

int main () {

    fmt::print("{}\n", leibniz_pi_approximation(10000));
    fmt::print("{}\n", leibniz_pi_approximation2(10000));
    fmt::print("{}\n", leibniz_pi_approximation2_alt(10000));

   return 0;
}
