
#include <vector>
#include <iostream>

#include <thrust/tabulate.h>

using namespace std;

auto main () -> int {

    auto odds = vector<int>(10);

    thrust::tabulate(
        odds.begin(), odds.end(), 
        [](auto e) { return e * 2 + 1; });

    for (auto odd : odds) 
        std::cout << odd << ' ';

}
