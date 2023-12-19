#pragma once

#include <fmt/core.h>

enum class card : char
{
    two = '2', three, four, five, six, seven, eight, nine, T, J, Q, K, A
};

template <>
struct fmt::formatter<card> {
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FmtContext>
    constexpr auto format(card card, FmtContext& ctx) {
        switch (card) {
            case card::two: return format_to(ctx.out(), "2");
            case card::three: return format_to(ctx.out(), "3");
            case card::four: return format_to(ctx.out(), "4");
            case card::five: return format_to(ctx.out(), "5");
            case card::six: return format_to(ctx.out(), "6");
            case card::seven: return format_to(ctx.out(), "7");
            case card::eight: return format_to(ctx.out(), "8");
            case card::nine: return format_to(ctx.out(), "9");
            case card::T: return format_to(ctx.out(), "T");
            case card::J: return format_to(ctx.out(), "J");
            case card::Q: return format_to(ctx.out(), "Q");
            case card::K: return format_to(ctx.out(), "K");
            case card::A: return format_to(ctx.out(), "A");
        }
    }
};

bool operator<(card c1, card c2);
bool operator>(card c1, card c2);
card to_card(char c);
