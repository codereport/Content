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
  auto const avg = _b1(div_(2.0), _plus_);
  return nums                                               //
         |> rv::zip_transform(avg,                          //
                              rv::take($, n),               //
                              rv::drop($, n) | rv::reverse) //
         |> std::ranges::min($);
}

auto main() -> int {

  std::cout << min_avg(std::vector{7, 8, 3, 4, 15, 13, 4, 1}) << '\n'; // 5.5
  std::cout << min_avg(std::vector{1, 2, 3, 7, 8, 9}) << '\n';         // 5.0

  return 0;
}