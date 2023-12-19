#include "hand_type_part2.h"

#include <array>
#include <algorithm>
#include <queue>
#include <unordered_map>

#include "card_part2.h"

bool operator<(hand_type_part2 ht1, hand_type_part2 ht2)
{ return static_cast<int>(ht1) < static_cast<int>(ht2); }

bool operator>(hand_type_part2 ht1, hand_type_part2 ht2)
{ return static_cast<int>(ht1) > static_cast<int>(ht2); }

hand_type_part2 determine_type_part2(const std::array<card_part2, 5>& cards)
{
    auto map = std::unordered_map<card_part2, size_t>();
    std::for_each(begin(cards), end(cards), [&map](card_part2 c) { ++map[c]; });

    auto pq = std::priority_queue<size_t>();
    std::for_each(begin(map), end(map),
            [&pq](const std::pair<card_part2, size_t>& p) { pq.push(p.second); });
    auto max = pq.top();
    pq.pop();
    auto second_max = pq.top();

    auto wildcard_cnt = map[card_part2::J];

    if (max == 5) {
        return hand_type_part2::five;
    } else if (max == 4) {
        return (wildcard_cnt) ? hand_type_part2::five : hand_type_part2::four;
    } else if (max == 3) {
        if (second_max == 2) {
            return (wildcard_cnt == max || wildcard_cnt == second_max) ?
                hand_type_part2::five : hand_type_part2::full_house;
        } else if (wildcard_cnt) {
            return hand_type_part2::four;
        } else {
            return hand_type_part2::three_one_kind;
        }
    } else if (max == 2) {
        if (second_max == 2) {
            if (wildcard_cnt == second_max)
                return hand_type_part2::four;
            else if (wildcard_cnt)
                return hand_type_part2::full_house;
            else
                return hand_type_part2::two_pair;
        } else {
            return (wildcard_cnt) ?
                hand_type_part2::three_one_kind : hand_type_part2::one_pair;
        }
    } else {
        return (wildcard_cnt) ? hand_type_part2::one_pair : hand_type_part2::high_card;
    }
}
