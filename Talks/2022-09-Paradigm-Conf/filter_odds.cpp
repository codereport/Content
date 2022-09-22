// Godbolt: https://godbolt.org/z/1Ena8zsGj

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

auto print(auto vec) {
  for (auto e : vec)
    std::cout << e << ' ';
  std::cout << '\n';
}

auto filter_evens(std::vector<int> list) {
  auto res = std::vector<int>{};
  for (auto num : list) {
    if (num % 2) {
      res.push_back(num);
    }
  }
  return res;
}

auto filter_evens1(std::vector<int> list) {
  auto it = std::erase_if(list, [](auto e) { return e % 2 == 0; });
  return list;
}

auto filter_evens2(std::vector<int> list) {
  return list | std::views::filter([](auto e) { return e % 2; });
}

auto main() -> int {
  auto const vec = std::vector{1, 2, 3, 4, 5};

  print(filter_evens(vec));
  print(filter_evens1(vec));
  print(filter_evens2(vec));

  return 0;
}
