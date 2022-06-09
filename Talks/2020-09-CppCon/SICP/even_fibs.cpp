
// https://www.godbolt.org/z/q9bdj9

#include <functional>
#include <iostream>
#include <ranges>

namespace rv = std::ranges::views;

auto fib(auto n) {
    using fun = std::function<int(int,int,int)>;
    fun fib_iter = [&](auto a, auto b, auto count) {
        return count == 0 ? b 
                          : fib_iter(a + b, a, count - 1);
    };
    return fib_iter(1, 0, n);
}

auto even_fibs(auto n) {
    return rv::iota(0, n+1)
         | rv::transform([](auto e) { return fib(e); })
         | rv::filter([](auto e) { return e % 2 == 0; });
}

int main() {

    for (auto e : even_fibs(20))
        std::cout << e << ' ';

    return 0;
}
