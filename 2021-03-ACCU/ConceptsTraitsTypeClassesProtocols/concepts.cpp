
// Godbolt: https://www.godbolt.org/z/zrafGW

#include <string>
#include <numbers>
#include <type_traits>
#include <concepts>
#include <fmt/core.h>

using namespace std::numbers;

class circle {
    float r;
public:
    explicit circle(float radius) : r{radius} {}
    auto name()      const -> std::string { return "Circle"; }
    auto area()      const -> float       { return pi * r * r; } 
    auto perimeter() const -> float       { return 2 * pi * r; }
};

class rectangle {
    float w, h;
public:
    explicit rectangle(float height, float width) : h{height}, w{width} {}
    auto name()      const -> std::string { return "Rectangle"; }
    auto area()      const -> float       { return w * h; } 
    auto perimeter() const -> float       { return 2 * w + 2 * h; }
};

template <typename S>
concept shape = requires(S s) {
    { s.name() }      -> std::same_as<std::string>;
    { s.area() }      -> std::floating_point;
    { s.perimeter() } -> std::floating_point;
};

void print_shape_info(shape auto s) {
    fmt::print("Shape: {}\nArea:  {}\nPerim: {}\n\n", 
        s.name(), s.area(), s.perimeter());
}

int main () {

    auto const c = circle{1};
    auto const r = rectangle{2, 3};

    print_shape_info(c);
    print_shape_info(r);

    return 0;
}
