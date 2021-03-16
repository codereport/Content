// C++ Version
// Godbolt Link: https://www.godbolt.org/z/TWMcr1

#include <algorithm>
#include <vector>

#include <fmt/format.h>

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

    fmt::print("{}\n", fmt::join(dog_owners, ", "));

}
