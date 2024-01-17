#pragma once

#include <fmt/core.h>
#include <fstream>
#include <type_traits>
#include <vector>

void solve_part1(std::ifstream&);

template<typename T1, typename T2>
struct fmt::formatter<std::pair<T1, T2>>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const std::pair<T1, T2>& p, FormatContext& ctx) {
        return format_to(ctx.out(), "[{}, {}]", p.first, p.second);
    }
};

template<typename Container>
std::enable_if_t<std::is_same_v<decltype(std::begin(std::declval<Container>())),
                     decltype(std::end(std::declval<Container>()))>,
    void> iterate_container(const Container& container)
{
    for (auto b = begin(container), e = end(container); b != e;) {
        fmt::print("{}", *b);
        if (++b != e)
            fmt::print("\t");
    }
    fmt::println("");
}
