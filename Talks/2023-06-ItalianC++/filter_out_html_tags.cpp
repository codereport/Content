// Godbolt: https://godbolt.org/z/on5xMG5ax

#include <algorithm>
#include <ranges>
#include <vector>
#include <https://raw.githubusercontent.com/codereport/blackbird/main/combinators.hpp>

#include <fmt/core.h>
#include <fmt/ranges.h>

#include <range/v3/range/conversion.hpp>

using namespace std::views;
using namespace combinators;

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
        |> values($)
        |> ranges::to<std::string>($);
}

auto filter_out_html_tags2(std::string_view sv) {
    return sv 
        |> transform($, _phi(_eq('<'), _or_, _eq('>')))
        |> zip_transform(_or_, $, scan_left($, true, _neq_))
        |> zip($, sv)
        |> filter($, _b(_not, _fst))
        |> values($)
        |> ranges::to<std::string>($);
}

int main() {
    fmt::print("{}\n", filter_out_html_tags ("<div>Hello <b>Italian C++!</b></div>"));
    fmt::print("{}\n", filter_out_html_tags2("<div>Hello <b>Italian C++!</b></div>"));

    return 0;
}