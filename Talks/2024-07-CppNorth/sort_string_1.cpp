#include <algorithm>
#include <iostream>
#include <span>
#include <string_view>
#include <vector>

using namespace std::string_literals;

auto sort_string(std::span<int> nums, std::string_view chars) -> std::string {
  auto pairs = std::vector<std::pair<int, char>>(nums.size());
  auto str = std::string(nums.size(), ' ');
  std::transform(nums.cbegin(), nums.cend(), chars.begin(), pairs.begin(),
                 [](auto i, auto c) {
                   return std::pair{i, c};
                 });
  std::sort(pairs.begin(), pairs.end());
  std::transform(pairs.cbegin(), pairs.cend(), str.begin(),
                 [](auto p) { return std::get<1>(p); });
  return str;
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