
// https://godbolt.org/z/4forbdGvM

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std::string_literals;

auto main() -> int {

    auto const play = "dog"s;
    auto const player_plays = std::vector{"cat", "dog", "mouse"};

    auto const rank = std::distance(
        std::find(
            player_plays.rbegin(), 
            player_plays.rend(),
            play), 
        player_plays.rend());

    std::cout << rank << '\n';

    return 0;
}
