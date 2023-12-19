#pragma once

#include <fmt/core.h>

#include "card.h"

enum class hand_type : int
{
    high_card, one_pair, two_pair, three_pair, full_house, four, five
};

template <>
struct fmt::formatter<hand_type>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FmtContext>
    constexpr auto format(const hand_type& type, FmtContext& ctx)
    {
        switch (type) {
            case hand_type::high_card: return format_to(ctx.out(), "high_card");
            case hand_type::one_pair: return format_to(ctx.out(), "one_pair");
            case hand_type::two_pair: return format_to(ctx.out(), "two_pair");
            case hand_type::three_pair: return format_to(ctx.out(), "three_pair");
            case hand_type::full_house: return format_to(ctx.out(), "full_house");
            case hand_type::four: return format_to(ctx.out(), "four");
            case hand_type::five: return format_to(ctx.out(), "five");
        }
    }
};

bool operator<(hand_type ht1, hand_type ht2);
bool operator>(hand_type ht1, hand_type ht2);
hand_type determine_type(const std::array<card, 5>& cards);
