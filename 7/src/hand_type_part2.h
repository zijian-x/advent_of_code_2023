#pragma once

#include <fmt/core.h>

#include "card_part2.h"

enum class hand_type_part2 : int
{
    high_card, one_pair, two_pair, three_one_kind, full_house, four, five
};

template <>
struct fmt::formatter<hand_type_part2>
{
    constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

    template <typename FmtContext>
    constexpr auto format(const hand_type_part2& type, FmtContext& ctx)
    {
        switch (type) {
            case hand_type_part2::high_card: return format_to(ctx.out(), "high_card");
            case hand_type_part2::one_pair: return format_to(ctx.out(), "one_pair");
            case hand_type_part2::two_pair: return format_to(ctx.out(), "two_pair");
            case hand_type_part2::three_one_kind: return format_to(ctx.out(), "three_one_kind");
            case hand_type_part2::full_house: return format_to(ctx.out(), "full_house");
            case hand_type_part2::four: return format_to(ctx.out(), "four");
            case hand_type_part2::five: return format_to(ctx.out(), "five");
        }
    }
};

bool operator<(hand_type_part2 ht1, hand_type_part2 ht2);
bool operator>(hand_type_part2 ht1, hand_type_part2 ht2);
hand_type_part2 determine_type_part2(const std::array<card_part2, 5>& cards);
