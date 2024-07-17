#include <algorithm>
#include <functional> // std::identity
#include <iostream>
#include <ranges>
#include <vector>

namespace rv = std::ranges::views; // std::views

auto is_array_special(std::vector<int> nums) -> bool {
  return std::ranges::all_of(           //
      rv::zip(nums, nums | rv::drop(1)) //
          | rv::transform([](auto t) {
              auto const [a, b] = t;
              return a % 2 != b % 2;
            }),
      std::identity{});
}

auto main() -> int {

  std::cout << is_array_special(std::vector{1, 2, 3, 4}) << '\n';    // 1
  std::cout << is_array_special(std::vector{1, 2, 3, 3, 4}) << '\n'; // 0

  return 0;
}