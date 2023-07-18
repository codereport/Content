// Godbolt: https://godbolt.org/z/x3zGPWT7q

#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

#include <https://raw.githubusercontent.com/codereport/blackbird/main/combinators.hpp>

#include <fmt/core.h>

int negatives_cpp_98(std::vector<int> nums) {
    int count = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] < 0) ++count;
    }
    return count;
}

int negatives_cpp_11(std::vector<int> nums) {
    int count = 0;
    for (auto num : nums) {
        if (num < 0) ++count;
    }
    return count;
}

auto negatives_cpp_14(std::vector<int> nums) -> int {
    int count = 0;
    for (auto num : nums) {
        if (num < 0) ++count;
    }
    return count;
}

auto negatives_cpp_14_algo(std::vector<int> nums) -> int {
    return std::count_if(nums.cbegin(), nums.cend(), 
        [](auto e) { return e < 0; });
}

auto negatives_cpp_20_algo(std::vector<int> nums) -> int {
    return std::ranges::count_if(nums, 
        [](auto e) { return e < 0; });
}

using namespace combinators;

auto negatives_cpp_20_algo_blackbird(std::vector<int> nums) -> int {
    return std::ranges::count_if(nums, lt_(0));
}


int main() {
    auto const nums = std::vector<int>{-3, 2, -1, 4, 5, 0}; 

    fmt::print("{}\n", negatives_cpp_98(nums));
    fmt::print("{}\n", negatives_cpp_11(nums));
    fmt::print("{}\n", negatives_cpp_14(nums));
    fmt::print("{}\n", negatives_cpp_14_algo(nums));
    fmt::print("{}\n", negatives_cpp_20_algo(nums));
    fmt::print("{}\n", negatives_cpp_20_algo_blackbird(nums));

    return 0;
}