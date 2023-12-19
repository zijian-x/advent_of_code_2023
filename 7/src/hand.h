#pragma once

#include <algorithm>
#include <array>
#include <fmt/core.h>
#include <queue>
#include <stdexcept>
#include <tuple>
#include <unordered_map>

#include "card.h"
#include "hand_type.h"

struct hand
{
    std::array<card, 5> cards;
    hand_type type;
    std::size_t bid;

    hand(const std::string& cards, std::size_t bid) : bid{bid}
    {
        for (size_t i = 0; i < this->cards.size(); ++i)
            this->cards[i] = to_card(cards[i]);

        type = determine_type(this->cards);
    }

    bool operator<(const hand& h2) const
    { return std::tie(type, cards) < std::tie(h2.type, h2.cards); }

    bool operator>(const hand& h2) const
    { return std::tie(type, cards) > std::tie(h2.type, h2.cards); }
};
