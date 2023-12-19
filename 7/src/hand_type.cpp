#include "hand_type.h"

#include <array>
#include <algorithm>
#include <queue>
#include <unordered_map>

bool operator<(hand_type ht1, hand_type ht2)
{ return static_cast<int>(ht1) < static_cast<int>(ht2); }

bool operator>(hand_type ht1, hand_type ht2)
{ return static_cast<int>(ht1) > static_cast<int>(ht2); }

hand_type determine_type(const std::array<card, 5>& cards)
{
    auto map = std::unordered_map<card, size_t>();
    std::for_each(begin(cards), end(cards), [&map](card c) { ++map[c]; });

    auto pq = std::priority_queue<size_t>();
    std::for_each(begin(map), end(map),
            [&pq](const std::pair<card, size_t>& p) { pq.push(p.second); });
    auto max = pq.top();
    pq.pop();
    auto second_max = pq.top();

    if (max == 5)
        return hand_type::five;
    else if (max == 4)
        return hand_type::four;
    else if (max == 3)
        return (second_max == 2) ? hand_type::full_house : hand_type::three_pair;
    else if (max == 2)
        return (second_max == 2) ? hand_type::two_pair : hand_type::one_pair;
    else
        return hand_type::high_card;
}
