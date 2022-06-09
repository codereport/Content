// CUDA Thrust
// Version 1 (bad)

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

auto main () -> int {

    auto const owners = vector<string>{"Conor", "Ashwin", "Lesley", "Sarah"};
    auto const pets   = vector<string>{"None",  "Dog",    "Cat",    "Dog"};

    auto dog_owners = vector<string>{};
    copy_if(
        owners.cbegin(), 
        owners.cend(), 
        back_inserter(dog_owners), 
        [pet = pets.cbegin()](auto const& owner) mutable {
            return *pet++ == "Dog";
        });

    for (auto const& o : dog_owners)
        cout << o << ' ';

}

// Version 2 using stencil (good / beautiful)

#include <vector>
#include <iostream>

#include <thrust/copy.h>

using namespace std;

auto main () -> int {

    auto const owners = vector<string>{"Conor", "Ashwin", "Lesley", "Sarah"};
    auto const pets   = vector<string>{"None",  "Dog",    "Cat",    "Dog"};

    auto dog_owners = vector<string>{};
    thrust::copy_if(
        owners.cbegin(), 
        owners.cend(), 
        pets.cbegin(),
        back_inserter(dog_owners), 
        [](auto const& pet) { return pet == "Dog"; });

    for (auto const& o : dog_owners)
        cout << o << ' ';

}
