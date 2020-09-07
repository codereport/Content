// https://www.godbolt.org/z/1qxshs

// C++20 Scheme Interpreter (in progress)

#include <iostream>
#include <functional> // function
#include <ranges>     // algorithms: copy; views: transform, take_while, drop
#include <string>                              // reverse, drop_while
#include <unordered_set>
#include <variant>
#include <vector>

#include <range/v3/view/slice.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/tail.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/range/conversion.hpp> // to

using namespace std::string_literals;
namespace rv = ranges::views;

std::unordered_set const special_forms = 
    { "cond"s, "cons"s, "define"s, "if"s, "lambda"s, "quote"s };

struct number { int value; };
struct string { std::string value; };
struct boolean {}; // TODO

struct _define {}; // TODO
struct _if {};     // TODO
struct _lambda {}; // TODO

using literal = std::variant<number, string, boolean>;
struct variable { std::string name; };
using special_form = std::variant<_define, _if, _lambda>; // TODO cons, cond, quote

// TODO replace with: 
// https://www.boost.org/doc/libs/1_60_0/doc/html/boost/algorithm/trim.html
[[nodiscard]]
auto trim(std::string const& exp) -> std::string {
    return exp 
        | std::ranges::views::drop_while([](auto c) { return c == ' ';})
        | std::ranges::views::reverse
        | std::ranges::views::drop_while([](auto c) { return c == ' ';})
        | std::ranges::views::reverse
        | ranges::to<std::string>;
}

class procedure_call {
public:
    explicit procedure_call(std::string input) :
        procedure_call{input 
            | rv::slice(1, static_cast<int32_t>(input.size()) - 1)
            | rv::split(' ')} {}

    [[nodiscard]] auto procedure() const noexcept { return _procedure; }
    [[nodiscard]] auto arguments() const noexcept { return _arguments; }

    void print() const {
        std::cout << _procedure << ' ';
        std::ranges::copy(_arguments, 
            std::ostream_iterator<std::string>{std::cout," "});
        std::cout << '\n';
    }

private:

    // using split_view = ranges::split_view<ranges::subrange<__gnu_cxx::__normal_iterator
    //     <char*, std::__cxx11::basic_string<char> >, __gnu_cxx::__normal_iterator
    //     <char*, std::__cxx11::basic_string<char> >, ranges::subrange_kind::sized>, 
    //     ranges::single_view<char> >;

    explicit procedure_call(auto /* split_view */ rng) : 
        _procedure{(rng 
            | rv::take(1) 
            | ranges::to<std::vector<std::string>>).front()},
        _arguments{rng 
            | rv::tail 
            | ranges::to<std::vector<std::string>>} 
    {
        std::cout << "#4 Procedure call: ";
        print();
    }

    std::string              _procedure;
    std::vector<std::string> _arguments;
};

using expression = std::variant<
    literal,             // aka self-evaluating
    variable,            // aka variable reference
    special_form,
    procedure_call>;     // aka application or combination

// primitive procedure pair
using ppp = std::pair<std::string, std::function<int(int,int)>>;

auto const primitive_procedures = std::vector<ppp>
    { {"+", [](int a, int b) { return a + b; }},
      {"*", [](int a, int b) { return a * b; }},
      {"-", [](int a, int b) { return a - b; }} };

[[nodiscard]]
auto is_literal(std::string const& input) -> bool {
    return std::isdigit(input.front()) // number{}
        || input.front() == '"';       // string{}
}

[[nodiscard]]
auto to_literal(std::string const& input) -> literal {
    std::cout << "#1 Literal\n";
    if (std::isdigit(input.front()))
        return number{std::stoi(input)};
    else {
        assert(input.front() == '"');
        return string{input};
    }
}

[[nodiscard]]
auto is_variable(std::string const& input) -> bool {
    return std::isalpha(input.front());
}

auto to_variable(std::string const& input) -> variable {
    return variable{input};
}

[[nodiscard]]
auto is_special_form(std::string const& input) -> std::optional<std::string> {
    // assert(input.front() == "("); TODO add to to_special_form
    if (input.front() != '(') return std::nullopt;
    auto const keyword = input
        | std::ranges::views::take_while([](auto c) { return c != ' '; })
        | std::ranges::views::drop(1)
        | ranges::to<std::string>;
    return special_forms.contains(keyword) ? std::optional{keyword} 
                                           : std::nullopt;
}

[[nodiscard]]
auto parse_expression(std::string const& input) -> expression {
    auto in = trim(input);
    if (is_literal(in))
        return to_literal(in);
    else if (is_variable(in))                               
        return to_variable(in);
    else if (auto sf = is_special_form(in); sf.has_value()) 
        return special_form{}; // to_special_form(sf.value());
    else                                                    
        return procedure_call{input};
}

[[nodiscard]]
auto is_primitive_procedure(std::string const& proc) -> bool {
    return ranges::find(primitive_procedures, proc, &ppp::first)
        != std::end(primitive_procedures);
}

using value_type = int; // int should probably std::variant of all "value types"

[[nodiscard]]
auto apply_primitive_procedure(std::string const& proc, auto const& args) -> value_type {
    // TODO this should be the result of eval(variable_reference) which is variable reference
    auto procedural_value = ranges::find(primitive_procedures, proc, &ppp::first)->second;
    return std::apply(procedural_value, args);
}

[[nodiscard]]
auto apply(std::string proc, auto args) -> value_type {
    if (is_primitive_procedure(proc))
        return apply_primitive_procedure(proc, args);
    return {};
}

auto eval(std::string const& input) -> value_type;

[[nodiscard]]
auto list_to_values(std::vector<std::string> const& expressions) {
    auto values = expressions
        | std::ranges::views::transform([](auto exp) { return eval(exp); })
        | ranges::to<std::vector<value_type>>;
    return std::make_tuple(values.front(), values.back());
}

[[nodiscard]]
auto eval(std::string const& input) -> value_type {
    if (auto const e = parse_expression(input); std::holds_alternative<literal>(e)) {
        // TODO use std::visit for all literals
        if (auto const l = std::get<literal>(e); std::holds_alternative<number>(l))
            return std::get<number>(l).value;
    }
    else if (std::holds_alternative<special_form>(e)) {
        auto const pc = std::get<special_form>(e);
        std::cout << "got special form\n";
    }
    else if (std::holds_alternative<procedure_call>(e)) {
        auto const pc = std::get<procedure_call>(e);
        return apply(pc.procedure(), list_to_values(pc.arguments()));
    }
    return 0;
}

int main() {
    std::cout << std::to_string( eval("(+ 1 2)") ) << '\n';
    std::cout << std::to_string( eval("(* 5 3)") ) << '\n';
    std::cout << std::to_string( eval("(- 6 4)") ) << '\n';
    std::cout << eval("(define x 42)") << '\n';
    std::cout << "(list \"cat\" \"dog\")" << '\n';
    return 0;
}
