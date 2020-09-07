// https://www.godbolt.org/z/1Mjjxs

// C++20 Scheme Interpreter (in progress)

#include <iostream>
#include <functional> // function
#include <ranges>     // copy
#include <string>
#include <unordered_set>
#include <variant>
#include <vector>

#include <range/v3/view/drop.hpp>
#include <range/v3/view/drop_while.hpp>
#include <range/v3/view/reverse.hpp>
#include <range/v3/view/slice.hpp>
#include <range/v3/view/split.hpp>
#include <range/v3/view/tail.hpp>
#include <range/v3/view/take_while.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/find.hpp>
#include <range/v3/range/conversion.hpp> // to

using namespace std::string_literals;
namespace rv = ranges::views;

std::unordered_set special_forms = 
    { "cond"s, "cons"s, "define"s, "if"s, "lambda"s, "quote"s };

struct number { int value; };
struct string { std::string value; };
struct boolean {}; // TODO

struct _define {}; // TODO
struct _if {};     // TODO
struct _lambda {}; // TODO

using literal = std::variant<number, string, boolean>;
struct variable_reference { std::string name; };
using special_form = std::variant<_define, _if, _lambda>; // TODO cons, cond, quote

// TODO replace with: 
// https://www.boost.org/doc/libs/1_60_0/doc/html/boost/algorithm/trim.html
auto trim(std::string const& exp) -> std::string {
    return exp 
        | rv::drop_while([](auto c) { return c == ' ';})
        | rv::reverse
        | rv::drop_while([](auto c) { return c == ' ';})
        | rv::reverse
        | ranges::to<std::string>;
}

class procedure_call {
public:
    explicit procedure_call(std::string input) :
        _sub_expressions(input 
            | rv::slice(1, static_cast<int32_t>(input.size()) - 1)
            | rv::split(' ')
            | ranges::to<std::vector<std::string>>) {
        std::cout << "#4 Procedure call: ";
        print(); //print2();
    }

    [[nodiscard]] auto procedure() const { return _sub_expressions.front(); }
    [[nodiscard]] auto operands()  const { return rv::tail(_sub_expressions) 
                                                | ranges::to<std::vector<std::string>>; }

    void print() const {
        std::ranges::copy(_sub_expressions, 
            std::ostream_iterator<std::string>{std::cout," "});
        std::cout << '\n';
    }

    void print2() const {
        for (auto e : _sub_expressions)
            std::cout << e << ' ';
        std::cout << '\n';
    }

private:
    std::vector<std::string> _sub_expressions;
};

using expression = std::variant<
    literal,             // aka self-evaluating
    variable_reference,
    special_form,
    procedure_call>;     // aka application or combination

// primitive procedure pair
using ppp = std::pair<std::string, std::function<int(int,int)>>;

auto const primitive_procedures = std::vector<ppp>
    { {"+", [](int a, int b) { return a + b; }},
      {"*", [](int a, int b) { return a * b; }},
      {"-", [](int a, int b) { return a - b; }} };

auto apply_primitive_procedure(auto proc, auto operands) {
    auto const res = [&] {
        // primitive-procedure?
        if (auto it = ranges::find(primitive_procedures, proc, &ppp::first);
                it != std::end(primitive_procedures))
            return std::apply(it->second, std::pair{std::stoi(operands.front()), 
                                                    std::stoi(operands.back())});
        return -1;
    } ();
    return std::to_string(res);
}

auto is_literal(std::string const& input) -> bool {
    return std::isdigit(input.front()) // number{}
        || input.front() == '"';       // string{}
}

auto to_literal(std::string const& input) -> literal {
    if (std::isdigit(input.front()))
        return number{std::stoi(input)};
    else {
        assert(input.front() == '"');
        return string{input};
    }
}

auto is_variable_reference(std::string const& input) -> bool {
    return std::isalpha(input.front());
}

auto to_variable_reference(std::string const& input) -> variable_reference {
    return variable_reference{input};
}

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

auto to_expression(std::string const& input) -> expression {
    auto trimmed_input = trim(input);
    if (is_literal(trimmed_input))
        return to_literal(trimmed_input);
    if (is_variable_reference(trimmed_input))
        return to_variable_reference(trimmed_input);
    if (auto sf = is_special_form(trimmed_input); sf.has_value())
        return special_form{};
    else 
        return procedure_call{input};
}

auto eval(std::string const& input) {
    auto const e = to_expression(input);
    if (std::holds_alternative<literal>(e)) {
        auto const l = std::get<literal>(e);
        std::cout << "got literal\n";
    }
    else if (std::holds_alternative<special_form>(e)) {
        auto const pc = std::get<special_form>(e);
        std::cout << "got special form\n";
    }
    else if (std::holds_alternative<procedure_call>(e)) {
        auto const pc = std::get<procedure_call>(e);
        return "   "s + apply_primitive_procedure(pc.procedure(), pc.operands());
    }
    return input;
}

int main() {
    std::cout << eval("(+ 1 2)") << '\n';
    std::cout << eval("(* 5 2)") << '\n';
    std::cout << eval("(- 6 3)") << '\n';
    std::cout << eval("(define x 42)") << '\n';
    std::cout << "(list \"cat\" \"dog\")" << '\n';
    return 0;
}
