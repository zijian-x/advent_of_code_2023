#include "part1.h"

#include <algorithm>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

#include "hand.h"

std::vector<hand> parse_hands(std::ifstream& input)
{
    auto hands = std::vector<hand>();
    for (auto line = std::string(); std::getline(input, line);) {
        auto split = line.find(' ');
        auto cards = line.substr(0, split);
        auto bid = std::stoull(line.substr(split, line.size()));

        hands.emplace_back(cards, bid);
    }

    return hands;
}

static void print(size_t i, const hand& hand)
{
    fmt::print("rank: {} ", i + 1);
    for (auto c : hand.cards)
        fmt::print("{}", c);
    fmt::println(" bid: {} type: {}", (i + 1),
            hand.bid, hand.type);
}

void solve_part1(std::ifstream& input)
{
    auto hands = parse_hands(input);
    std::sort(begin(hands), end(hands));

    auto sum = 0ull;
    for (size_t i = 0; i < hands.size(); ++i) {
        // print(i, hands[i]);
        sum += (i + 1) * hands[i].bid;
    }
    fmt::println("sum: {}", sum);
}
