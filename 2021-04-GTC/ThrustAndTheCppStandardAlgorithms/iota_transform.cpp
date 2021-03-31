// Godbolt: https://www.godbolt.org/z/crv61E9b3

#include <numeric>
#include <algorithm>
#include <vector>

#include <fmt/format.h>

using namespace std;

auto main () -> int {

    auto odds = vector<int>(10);

    iota(odds.begin(), odds.end(), 0);
    transform(
        odds.begin(), 
        odds.end(), 
        odds.begin(),
        [](auto e) { return e * 2 + 1; });

    fmt::print("{}\n", fmt::join(odds, ", "));

}
