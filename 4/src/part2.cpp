#include "part2.h"

#include <algorithm>
#include <fmt/core.h>
#include <iterator>
#include <numeric>
#include <sstream>
#include <unordered_set>
#include <utility>
#include <vector>

auto card_count_and_scores(std::ifstream& input)
    -> std::vector<std::pair<size_t, size_t>>
{
    auto matches = std::vector<std::pair<size_t, size_t>>();

    auto line = std::string();
    while (std::getline(input, line)) {
        auto iss = std::istringstream(line);
        auto words = std::vector<std::string>(std::istream_iterator<std::string>{iss},
                std::istream_iterator<std::string>{});
        auto lucky_nums = std::unordered_set<int>();
        auto score = 0;

        auto check_num = false;
        for (size_t i = 2; i < words.size(); ++i) {
            if (words[i] == "|") {
                check_num = true;
                continue;
            }

            auto num = std::stoi(words[i]);
            if (!check_num)
                lucky_nums.insert(num);
            else if (lucky_nums.count(num))
                ++score;
        }

        matches.emplace_back(1, score);
    }

    return matches;
}

void solve_part2(std::ifstream& input)
{
    auto stack = card_count_and_scores(input); // card count, card score
    for (size_t i = 0; i < stack.size(); ++i) {
        const auto& [cnt, score] = stack[i];
        for (size_t j = 1; j <= score; ++j) {
            if (i + j < stack.size())
                stack[i + j].first += cnt;
        }
    }

    size_t total = std::accumulate(begin(stack), end(stack),
            static_cast<size_t>(0),
            [](size_t sum, const std::pair<size_t, size_t>& card_pair) {
                return sum + card_pair.first;
            });

    fmt::println("{}", total);
}
