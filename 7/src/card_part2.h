#pragma once

#include <fmt/core.h>

enum class card_part2 : char
{
    J = '1', two, three, four, five, six, seven, eight, nine, T, Q, K, A
};

template <>
struct fmt::formatter<card_part2> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FmtContext>
    constexpr auto format(card_part2 card, FmtContext& ctx) {
        switch (card) {
            case card_part2::two: return format_to(ctx.out(), "2");
            case card_part2::three: return format_to(ctx.out(), "3");
            case card_part2::four: return format_to(ctx.out(), "4");
            case card_part2::five: return format_to(ctx.out(), "5");
            case card_part2::six: return format_to(ctx.out(), "6");
            case card_part2::seven: return format_to(ctx.out(), "7");
            case card_part2::eight: return format_to(ctx.out(), "8");
            case card_part2::nine: return format_to(ctx.out(), "9");
            case card_part2::T: return format_to(ctx.out(), "T");
            case card_part2::J: return format_to(ctx.out(), "J");
            case card_part2::Q: return format_to(ctx.out(), "Q");
            case card_part2::K: return format_to(ctx.out(), "K");
            case card_part2::A: return format_to(ctx.out(), "A");
        }
    }
};

bool operator<(card_part2 c1, card_part2 c2);
bool operator>(card_part2 c1, card_part2 c2);
card_part2 to_card_part2(char c);
