// Godbolt: https://godbolt.org/z/3Yndh1Pvf

#include <algorithm>
#include <ranges>
#include <vector>

#include <fmt/core.h>
#include <fmt/ranges.h>

using namespace std::views;

auto scan_left(auto rng, auto init, auto op) {
    return transform(rng, [first = true, acc = init, op](auto e) mutable {
            if (first) first = false; 
            else acc = op(acc, e);
            return acc;
        });
}

auto filter_out_html_tags(std::string_view sv) {
    return sv 
        |> transform($, [](auto e) { return e == '<' or e == '>'; })
        |> zip_transform(std::logical_or{}, $, scan_left($, true, std::not_equal_to{}))
        |> zip($, sv)
        |> filter($, [](auto t) { return not std::get<0>(t); })
        |> transform($, [](auto t) { return std::get<1>(t); });
}

int main() {
    fmt::print("{}\n", filter_out_html_tags("<div>Hello <b>Italian C++!</b></div>"));

    return 0;
}
