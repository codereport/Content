#include "parrot.hpp"

auto sos(int N) {
    return parrot::range(N)  //
      .sq()
      .sum();
}

int main() { sos(10).print(); }
