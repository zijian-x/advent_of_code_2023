#pragma once

#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <unordered_map>

#include "card_part2.h"
#include "hand_type_part2.h"

struct hand_part2
{
    std::array<card_part2, 5> cards;
    hand_type_part2 type;
    std::size_t bid;

    hand_part2(const std::string& cards, std::size_t bid) : bid{bid}
    {
        for (size_t i = 0; i < this->cards.size(); ++i)
            this->cards[i] = to_card_part2(cards[i]);

        type = determine_type_part2(this->cards);
    }

    bool operator<(const hand_part2& h2) const
    { return std::tie(type, cards) < std::tie(h2.type, h2.cards); }

    bool operator>(const hand_part2& h2) const
    { return std::tie(type, cards) > std::tie(h2.type, h2.cards); }
};
