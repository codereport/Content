#include "parrot.hpp"

auto mode(auto data) {
    return data  //
      .sort()
      .rle()
      .max_by_key(parrot::snd());
}

int main() {
    auto data = parrot::scalar(9).repeat(30).rand().print();
    mode(data).print();
}
