#include <algorithm>
#include <ranges>
#include <vector>

#include <fmt/ranges.h>

using namespace std::views;
using namespace combinators;

// original youtube comment from OMGclueless
// auto sushi_for_two(std::vector<int> sushi) {
//     std::vector<int> runs;
//     int current_run = 1;
//     for (int i = 1; i < N; ++i) {
//         if (sushi[i] == sushi[i - 1]) ++current_run;
//         else { runs.push_back(current_run); current_run = 1; }
//     }
//     runs.push_back(current_run);

//     int max_run = runs[0];
//     for (int i = 1; i < runs.size(); ++i) {
//         max_run = std::max(max_run, std::min(runs[i], runs[i - 1]));
//     }
//     return 2 * max_run;
// }

// fix compilation error (N should be sushi.size())
auto sushi_for_two_wrong(std::vector<int> sushi) {
    std::vector<int> runs;
    int current_run = 1;
    for (int i = 1; i < sushi.size(); ++i) {
        if (sushi[i] == sushi[i - 1]) ++current_run;
        else { runs.push_back(current_run); current_run = 1; }
    }
    runs.push_back(current_run);

    int max_run = runs[0];
    for (int i = 1; i < runs.size(); ++i) {
        max_run = std::max(max_run, std::min(runs[i], runs[i - 1]));
    }
    return 2 * max_run;
}

// working but not formatted
auto sushi_for_two_correct(std::vector<int> sushi) {
    std::vector<int> runs;
    int current_run = 1;
    for (int i = 1; i < sushi.size(); ++i) {
        if (sushi[i] == sushi[i - 1]) ++current_run;
        else { runs.push_back(current_run); current_run = 1; }
    }
    runs.push_back(current_run);

    int max_run = std::min(runs[0], runs[1]);
    for (int i = 2; i < runs.size(); ++i) {
        max_run = std::max(max_run, std::min(runs[i], runs[i - 1]));
    }
    return 2 * max_run;
}

// working and formatting
auto sushi_for_two(std::vector<int> sushi) {
    std::vector<int> runs;
    int current_run = 1;
    for (int i = 1; i < sushi.size(); ++i) {
        if (sushi[i] == sushi[i - 1]) ++current_run;
        else { 
            runs.push_back(current_run); 
            current_run = 1; 
        }
    }
    runs.push_back(current_run);

    int max_run = std::min(runs[0], runs[1]);
    for (int i = 2; i < runs.size(); ++i) {
        max_run = std::max(max_run, std::min(runs[i], runs[i - 1]));
    }
    return 2 * max_run;
}

auto main() -> int {

    fmt::print("{}\n", sushi_for_two ({2, 2, 2, 1, 1, 2, 2}));       // 4
    fmt::print("{}\n", sushi_for_two ({1, 2, 1, 2, 1, 2}));          // 2
    fmt::print("{}\n", sushi_for_two ({2, 2, 1, 1, 1, 2, 2, 2, 2})); // 6

    return 0;
}
