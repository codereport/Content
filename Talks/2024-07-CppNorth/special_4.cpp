#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include <combinators.hpp>

using namespace combinators;

namespace rv = std::ranges::views; // std::views

auto is_array_special(std::vector<int> nums) -> bool {
  return std::ranges::all_of( //
      rv::adjacent_transform<2>(nums, _psi(_neq_, _odd)), _id);
}

auto main() -> int {

  std::cout << is_array_special(std::vector{1, 2, 3, 4}) << '\n';    // 1
  std::cout << is_array_special(std::vector{1, 2, 3, 3, 4}) << '\n'; // 0

  return 0;
}