#include "part2.h"

#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

#include "hand_part2.h"

static std::vector<hand_part2> parse_hands(std::ifstream& input)
{
    auto hands = std::vector<hand_part2>();
    for (auto line = std::string(); std::getline(input, line);) {
        auto split = line.find(' ');
        auto cards = line.substr(0, split);
        auto bid = std::stoull(line.substr(split, line.size()));

        hands.emplace_back(cards, bid);
    }

    return hands;
}

static void print(size_t rank, const hand_part2& hand_part2)
{
    fmt::print("rank: {} ", rank);
    for (auto c : hand_part2.cards)
        fmt::print("{}", c);
    fmt::println(" bid: {} type: {}", hand_part2.bid, hand_part2.type);
}

void solve_part2(std::ifstream& input)
{
    auto hands = parse_hands(input);
    for (size_t i = 0; i < hands.size(); ++i)
        print(i + 1, hands[i]);
    std::sort(begin(hands), end(hands));

    auto sum = 0ull;
    for (size_t i = 0; i < hands.size(); ++i) {
        print(i + 1, hands[i]);
        sum += (i + 1) * hands[i].bid;
    }
    fmt::println("sum: {}", sum);
}
