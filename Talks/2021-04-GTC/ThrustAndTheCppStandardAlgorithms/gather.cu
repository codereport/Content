
#include <vector>
#include <iostream>

#include <thrust/gather.h>

using namespace std;

auto main () -> int {

    auto const deck       = vector<int>{13, 2, 14, 3, 6, 7};
    auto const gather_map = vector<int>{0, 2, 4};
    auto hand             = vector<int>(3);

    // deals every second card to hand
    thrust::gather(
        gather_map.cbegin(),
        gather_map.cend(),
        deck.cbegin(),
        hand.begin());
        
    for (auto card : hand) 
        std::cout << card << ' ';

}
