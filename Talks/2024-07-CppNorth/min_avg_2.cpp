#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include <combinators.hpp>

using namespace combinators;

namespace rv = std::ranges::views; // std::views

auto min_avg(std::vector<int> nums) -> float {
  std::ranges::sort(nums);
  auto const n = nums.size() / 2;
  return std::ranges::min(rv::zip_transform(std::plus{}, rv::take(nums, n),
                                            rv::drop(nums, n) | rv::reverse) //
                          | rv::transform(div_(2.0)));
}

auto main() -> int {

  std::cout << min_avg(std::vector{7, 8, 3, 4, 15, 13, 4, 1}) << '\n'; // 5.5
  std::cout << min_avg(std::vector{1, 2, 3, 7, 8, 9}) << '\n';         // 5.0

  return 0;
}