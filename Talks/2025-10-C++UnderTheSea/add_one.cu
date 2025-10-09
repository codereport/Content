#include "parrot.hpp"

auto add_one(auto matrix) { return matrix + 1; }

int main() {
    auto matrix = parrot::range(9).reshape({3, 3});
    add_one(matrix).print();
}