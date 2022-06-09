// C++ Version
// Godbolt Link: https://www.godbolt.org/z/PGqPqv

#include <numeric>
#include <vector>

#include <fmt/core.h>

using namespace std;

auto main () -> int {

    auto const vals = vector<int>{42, 1729, 4104};

    auto const sum_evens = accumulate(
        vals.cbegin(), vals.cend(), 0, 
        [](auto acc, auto val) { 
            return acc + (val % 2 == 0 ? val : 0); 
        });

    fmt::print("{}\n", sum_evens); // 4146

}
