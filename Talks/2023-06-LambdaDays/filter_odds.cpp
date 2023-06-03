#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

auto filter_odds(std::vector<int> nums) {
  auto odds = std::vector<int>{};
  for (auto const num : nums)
    if (num % 2 == 1)
      odds.push_back(num);
  return odds;
}

auto filter_odds2(std::vector<int> nums) {
  auto odds = std::vector<int>{};
  std::copy_if(nums.begin(), nums.end(), std::back_inserter(odds),
               [](auto e) { return e % 2 == 1; });
  return odds;
}

auto filter_odds3(std::vector<int> nums) {
  auto odds = std::vector<int>{};
  std::ranges::copy_if(nums, std::back_inserter(odds),
                       [](auto e) { return e % 2 == 1; });
  return odds;
}

auto filter_odds4(std::vector<int> nums) {
  return nums | std::views::filter([](auto e) { return e % 2 == 1; });
}

auto mod_ = [](auto x) { return [x](auto y) { return y % x; }; };

auto filter_odds5(std::vector<int> nums) {
  return nums | std::views::filter(mod_(2));
}

auto print(auto vec) {
  for (auto e : vec)
    std::cout << e << ' ';
  std::cout << '\n';
}

auto main() -> int {

  auto const vec = std::vector{1, 2, 3, 4, 5, 6, 7};

  print(filter_odds(vec));
  print(filter_odds2(vec));
  print(filter_odds3(vec));
  print(filter_odds4(vec));
  print(filter_odds5(vec));

  return 0;
}

// filterOdds = filter odd