#include <iostream>
#include <ranges>
#include <vector>

auto add_one(auto& matrix) {
    for (auto& row : matrix) {
        for (auto& e : row) { e += 1; }
    }
    return matrix;
}

auto add_one_ranges(const auto& matrix) {
    return matrix | std::ranges::views::transform([](const auto& row) {
               return row | std::ranges::views::transform(
                              [](auto e) { return e + 1; });
           });
}

int main() {
    auto matrix = std::vector<std::vector<int>>{
      {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto result = add_one(matrix);
    for (auto row : result) {
        for (auto cell : row) { std::cout << cell << " "; }
        std::cout << std::endl;
    }
    auto result_ranges = add_one_ranges(matrix);
    for (auto row : result_ranges) {
        for (auto cell : row) { std::cout << cell << " "; }
        std::cout << std::endl;
    }
    return 0;
}