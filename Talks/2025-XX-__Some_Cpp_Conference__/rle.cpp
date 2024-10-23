// Compiler Explorer: https://godbolt.org/z/YM9xzKb9K

#include <print>
#include <ranges>
#include <algorithm>
#include <string>

auto run_length_encode(auto rng) {
    return std::views::chunk_by(rng, std::equal_to{})
        | std::views::transform([](auto chunk) {
            return std::pair{
                chunk.front(), 
                std::ranges::distance(chunk)
            };
        });
}

auto main() -> int {
    auto const s = std::string{"hello"};
    for (auto [a, b] : run_length_encode(s))
        std::println("{}: {}", a, b);

}