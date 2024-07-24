#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <string_view>
#include <vector>

#include <range/v3/action/sort.hpp>
#include <range/v3/range/conversion.hpp>

#include <combinators.hpp>

using namespace combinators;

using namespace std::string_literals;

namespace rv = std::ranges::views; // std::views
namespace v3 = ranges;

auto sort_string(std::span<int> nums, std::string_view chars) -> std::string {
  return rv::zip(nums, chars)   //
         | v3::to<std::vector>  //
         | v3::action::sort     //
         | rv::transform(_snd)  //
         | v3::to<std::string>;
}

auto main() -> int {

  auto a = std::vector{3, 2, 1, 4};
  auto b = std::vector{2, 4, 1, 3};
  auto c = std::vector{5, 4, 2, 6, 1, 3};

  std::cout << sort_string(a, "REPL"s) << '\n';   // "PERL"
  std::cout << sort_string(b, "AURK"s) << '\n';   // "RAKU"
  std::cout << sort_string(c, "OHYNPT"s) << '\n'; // "PYTHON"

  return 0;
}