
// https://godbolt.org/z/KE7EsbMrY

#include <functional>
#include <string>
#include <string_view>

#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp> 
#include <range/v3/view/partial_sum.hpp> 
#include <range/v3/view/transform.hpp> 
#include <range/v3/view/zip.hpp> 
#include <range/v3/view/zip_with.hpp> 

#include <fmt/core.h>
#include <fmt/ranges.h>

namespace rv = ranges::views;

auto filter_out_html_tags(std::string_view sv) {
    auto angle_bracket_mask = 
        sv | rv::transform([](auto e) { return e == '<' or e == '>'; });
    return rv::zip(rv::zip_with(std::logical_or{}, 
            angle_bracket_mask, 
            angle_bracket_mask | rv::partial_sum(std::not_equal_to{})), sv)
        | rv::filter([](auto t) { return not std::get<0>(t); })
        | rv::transform([](auto t) { return std::get<1>(t); })
        | ranges::to<std::string>;
}

// auto filter_out_html_tags(std::string_view sv) {
//     return sv 
//         |  rv::transform(_phi(_eq('<'), _or_, _eq('>')))
//         |> rv::zip_with(_or_, _, _ | rv::scan_left(_not_eq_))
//         |> rv::zip(_, sv)
//         |  rv::filter(_b(_not, _get<0>{}))
//         |  rv::transform(_get<1>{})
//         |  ranges::to<std::string>;
// }

int main() {
    fmt::print("{}\n", filter_out_html_tags("<div>Hello <b>CppNorth!</b></div>"));

    return 0;
}
