#include <algorithm>
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp>

#include <combinators.hpp>

using namespace combinators;

using namespace std::string_literals;

namespace rv = std::ranges::views; // std::views
namespace v3 = ranges;

auto sort_string(std::vector<int> nums, std::string_view chars) -> std::string {
  return rv::zip(nums, chars)   //
         | v3::to<std::vector>  //
         | ranges::action::sort //
         | rv::transform(_snd)  //
         | v3::to<std::string>;
}

auto main() -> int {

  std::cout << sort_string(std::vector{3, 2, 1, 4}, "REPL"s) << '\n'; // "PERL"
  std::cout << sort_string(std::vector{2, 4, 1, 3}, "AURK"s) << '\n'; // "RAKU"
  std::cout << sort_string(std::vector{5, 4, 2, 6, 1, 3}, "OHYNPT"s)
            << '\n'; // "RAKU"

  return 0;
}